/*
  AD7714 (Delta-Sigma ADC) testing code
  March 2018
  By. Abdullah Al-Nafisah and Mojtaba Al-Shams

  External connections:
  PIN 1 -> SCLK : external clock SPI Arduino (pin 52 MEGA) (pin 13 nano) Arduino
  PIN 2 -> MCLK IN : 2.4576 MHz by crystal (input)
  PIN 3 -> MCLK OUT : 2.4576 MHz (output)
  PIN 4 -> POL = 0: first transition of the serial clock in a data transfer operation is from a low to a high
  PIN 5 -> (SYNC) = 1 : synchronization of the digital filters and analog modulators
  PIN 6 -> (RESET) : Reset (PIN 49 MEGA) (pin 9 nano) Arduino
  PIN 7/8/9/10 -> AIN1/AIN2/AIN3/AIN4 : Analog Input Channel
  PIN 11 -> (STANDBY) = 1 : disable Standby
  PIN 12 -> AVdd = 5 V
  PIN 13 -> BUFFER = 0 : analog input is shorted out
  PIN 14 -> REF IN(-) = AGND : negative input of the differential reference input
  PIN 15 -> REF IN(+) = 2.5 V : positive input of the differential reference input
  PIN 16/17 -> AIN5/AIN6 : Analog Input Channel
  PIN 18 -> AGND = GND
  PIN 19 -> (CS) : chip select SPI (PIN 53 MEGA) (pin 10 nano) Arduino
  PIN 20 -> (DRDY) : logic input of the AD7714 (PIN 48 MEGA) (pin 6 nano) Arduino
  PIN 21 -> DOUT : serial data output, MISO SPI (PIN 50 MEGA) (pin 12 nano) Arduino
  PIN 22 -> DIN : serial data input, MOSI SPI (PIN 51 MEGA) (pin 11 nano) Arduino
  PIN 23 -> DVdd = 5 V
  PIN 24 -> DGND = GND
*/
//----------------------------------------------------------------------------------------------------
// Used Libraries
#include <SPI.h>
#include <SoftwareSerial.h>
//#include <SD.h>
//----------------------------------------------------------------------------------------------------
// Timer
int c = 0;
int i = 0;
int Stop;
long StartTimer;
long FinishTimer;
long TotaTime;
//----------------------------------------------------------------------------------------------------
// ADC parameters
const int ADC_CS = 10;
const int Reset = 9;
const int DRDY = 6;
unsigned long Data;
signed long Volt;
byte D[3];
SPISettings ADCsettings(2000000, MSBFIRST, SPI_MODE3);
//----------------------------------------------------------------------------------------------------
// Wireless Communication parameters
int DD;
const int Rx = 3;
const int Tx = 4;
SoftwareSerial mySerial = SoftwareSerial(Rx, Tx);
//----------------------------------------------------------------------------------------------------
// SD Card parameters
//const int SD_CS = 4;
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(2000000);
  // Wait for serial port to connect
  while (!Serial) {}
  //--------------------------------------------------------------------------------------------------
  // Define pins
  pinMode(DRDY, INPUT);
  pinMode(Reset, OUTPUT);
  pinMode(ADC_CS, OUTPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(ADC_CS, HIGH);
  //--------------------------------------------------------------------------------------------------
  // Wireless Communication
  // Set the data rate
  mySerial.begin(19200);
  Serial.println("Wireless Seismic Acquisition, Serial Communication is ON");
  mySerial.println("Hello, Transmitter is talking");
  //--------------------------------------------------------------------------------------------------
  // ADC
  // Wake up the SPI bus
  SPI.begin();
  // Resetting 1
  digitalWrite(ADC_CS, LOW);
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  digitalWrite(ADC_CS, HIGH);
  // Resetting 2
  SPI.beginTransaction(ADCsettings);
  digitalWrite(ADC_CS, LOW);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  digitalWrite(ADC_CS, HIGH);
  SPI.endTransaction();
  // Configuring
  SPI.beginTransaction(ADCsettings);
  digitalWrite(ADC_CS, LOW);
  SPI.transfer(0x26); // Filter (high) (Differential 26) (Single ended 20)
  SPI.transfer(0x40); //
  SPI.transfer(0x36); // Filter (low) (Differential 36) (Single ended 30)
  SPI.transfer(0x26); //
  SPI.transfer(0x16); // Mode (Differential 16) (Single ended 10)
  SPI.transfer(0x20); // With gain (3C=8)(28=4), Without  20
  digitalWrite(ADC_CS, HIGH);
  SPI.endTransaction();
  delay(100);
  //--------------------------------------------------------------------------------------------------
  // SD Card
  /*
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.beginTransaction(SDsettings);
    digitalWrite(SD_CS, LOW);
    Serial.print("Initializing SD card...");
    // see if the card is present and can be initialized:
    if (!SD.begin(SD_CS)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
    }
    Serial.println("card initialized.");
    digitalWrite(SD_CS, HIGH);
    SPI.endTransaction();
  */
  //--------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
void loop() {
  Stop = digitalRead(5);
  FinishTimer = millis();
  while (Stop == 1)
  {
    if (i == 1)
    {
      FinishTimer = millis();
      Serial.println("---------------------");
      Serial.print("Start Time: ");
      Serial.println(StartTimer);
      Serial.print("Finish Time: ");
      Serial.println(FinishTimer);
      TotaTime = (FinishTimer - StartTimer);
      Serial.print("Total Time (in milli-seconds): ");
      Serial.println(TotaTime);
      Serial.print("---------------------");
      i = 0;
    }
    c = 0;
    Stop = digitalRead(2);
  }

  if (i == 0)
  {
    StartTimer = millis();
    i = 1;
    Serial.println("---------------------");
  }
  //--------------------------------------------------------------------------------------------------
  // ADC part
  if (digitalRead(DRDY) == LOW) {
    SPI.beginTransaction(ADCsettings);
    digitalWrite(ADC_CS, LOW);
    SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[0] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[1] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[2] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    digitalWrite(ADC_CS, HIGH);
    SPI.endTransaction();
    //------------------------------------------------------------------------------------------------
    // Calculations
    Data = (float)D[2] + (float)D[1] * 256 + (float)D[0] * 256 * 256;
    Volt = 1000.0 * (Data / 3355443.2) - 2500.0;
    //Serial.println(Volt);
    //------------------------------------------------------------------------------------------------
    // Wireless Communication
    DD = (int)(Volt + 2500);
    mySerial.println(DD);
    //------------------------------------------------------------------------------------------------
    // SD Card
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    /*
      SPI.beginTransaction(SDsettings);
      digitalWrite(SD_CS, LOW);
      File dataFile = SD.open("datalog.txt", FILE_WRITE);
      // if the file is available, write to it:
      if (dataFile) {
      dataFile.println(Volt);
      dataFile.close();
      // print to the serial port too:
      }
      // if the file isn't open, pop up an error:
      else {
      Serial.println("error opening datalog.txt");
      }
      digitalWrite(SD_CS, HIGH);
      SPI.endTransaction();
    */
  }
  //--------------------------------------------------------------------------------------------------
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
