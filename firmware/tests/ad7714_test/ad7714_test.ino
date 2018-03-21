/*
  AD7714 (Delta-Sigma ADC) testing code
  March 2018
  By. Abdullah Alnafisah

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

//--------------------------------------------------

// SPI library
#include <SPI.h>
const int CS = 10;
const int Reset = 9;
const int DRDY = 6;
unsigned long Data;
signed long Volt;

byte D[3];

SPISettings settings(100000, MSBFIRST, SPI_MODE3);

//--------------------------------------------------
void setup() {
  Serial.begin(2000000);
  // Define pins
  pinMode(CS, OUTPUT);
  pinMode(Reset, OUTPUT);
  pinMode(DRDY, INPUT);
  digitalWrite(Reset, HIGH);
  digitalWrite(CS, HIGH);
  // Wake up the SPI bus
  SPI.begin();
  // Resetting
  digitalWrite(CS, LOW);
  digitalWrite(Reset, LOW);
  delay(100);
  digitalWrite(Reset, HIGH);
  digitalWrite(CS, HIGH);
  SPI.beginTransaction(settings);
  digitalWrite(CS, LOW);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  SPI.transfer(0xFF);
  digitalWrite(CS, HIGH);
  SPI.endTransaction(); 
  // Configuring
  SPI.beginTransaction(settings);
  digitalWrite(CS, LOW);
  SPI.transfer(0x26); // Filter (high) (Differential 26) (Single ended 20)
  SPI.transfer(0x43); //40
  SPI.transfer(0x36); // Filter (low) (Differential 36) (Single ended 30)
  SPI.transfer(0xE8); //13
  SPI.transfer(0x16); // Mode (Differential 16) (Single ended 10)
  SPI.transfer(0x20); //
  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  delay(100);
}

//--------------------------------------------------
void loop() {
  if (digitalRead(DRDY) == LOW) {
    SPI.beginTransaction(settings);
    digitalWrite(CS, LOW);
    SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[0] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[1] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    D[2] = SPI.transfer(0x5E); // (Differential 5E) (Single ended 58)
    digitalWrite(CS, HIGH);
    SPI.endTransaction();
    Data = (float)D[2]+(float)D[1]*256+(float)D[0]*256*256;
    Volt = 1000.0*(Data/3355443.2)-2500;
    
    Serial.println(Volt);
  }
}
