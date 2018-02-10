// 12 bits successive approximation ADC test
// Chip #: AD574ALN
// By: Abdullah Al-Nafisah, email:abdullahynafisah@hotmail.com
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(19, 20); // CE, CSN
const byte address[6] = "00001";
double wave;

double fs;
int c=0;
int i=0;
int Stop;
long StartTimer;
long FinishTimer;
int tsr = 1;
int tsc = 1;
const int AnalogInput = 14;
const int ReadConvert = 13;
int Level;
float Voltage;
int D0;
int D1;
int D2;
int D3;
int D4;
int D5;
int D6;
int D7;
int D8;
int D9;
int D10;
int D11;
int Status;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(ReadConvert, OUTPUT);
  pinMode(AnalogInput, OUTPUT);
}

void loop() {
  
  Stop = digitalRead(17);
  FinishTimer = millis();
  while (Stop == 1)
  {
    if (i==1)
    {
    FinishTimer = millis();
    Serial.println("---------------------");
    Serial.print("Start Time: ");
    Serial.println(StartTimer);
    Serial.print("Finish Time: ");
    Serial.println(FinishTimer);
    fs = c/((FinishTimer-StartTimer)*1000);
    Serial.print("Sampling Frequency: ");
    Serial.println(fs);
    Serial.print("---------------------");
    i = 0;
    }
    c =0;
    Stop = digitalRead(17);
  }
  
  if (i==0)
  {
    StartTimer = millis();
    i = 1;
    Serial.println("---------------------");
  }
  digitalWrite(ReadConvert, HIGH);
  //Serial.print("Status1:\t");
  //Serial.print(Status);
  //Serial.print("\t\t");
  //delay(tsr);// Time to read the analog signal
  //Serial.print("Status2:\t");
  //Serial.println(Status);
  digitalWrite(ReadConvert, LOW);
  //Serial.print("Status3:\t");
  //Serial.print(Status);
  //Serial.print("\t\t");
  //delay(tsc);// Time to convert the analog signal to digital
  //Serial.print("Status4:\t");
  //Serial.println(Status);

  D0 = digitalRead(12);
  D1 = digitalRead(11);
  D2 = digitalRead(10);
  D3 = digitalRead(9);
  D4 = digitalRead(8);
  D5 = digitalRead(7);
  D6 = digitalRead(6);
  D7 = digitalRead(5);
  D8 = digitalRead(4);
  D9 = digitalRead(3);
  D10 = digitalRead(2);
  D11 = digitalRead(15);
  Status = digitalRead(16);
  c++;
  Level = 2048 * D11 + 1028 * D10 + 512 * D9 + 256 * D8 + 128 * D7 + 64 * D6 + 32 * D5 + 16 * D4 + 8 * D3 + 4 * D2 + 2 * D1 + D0;
  //Serial.println(Level);
  Voltage = 1000.0*(Level-2048)/405.0;
  Serial.println(Voltage);
  //radio.write(&Voltage, sizeof(Voltage));

  /*
    Serial.print("Analog input = ");
    Serial.println(5.0*(AnalogSignal/255.0));
    Serial.print("Digital output = ");
    Serial.print(D11);
    Serial.print(D10);
    Serial.print(D9);
    Serial.print(D8);
    Serial.print(D7);
    Serial.print(D6);
    Serial.print(D5);
    Serial.print(D4);
    Serial.print(D3);
    Serial.print(D2);
    Serial.print(D1);
    Serial.println(D0);
    Serial.print("Level number = ");
    Serial.println(Level);
    Serial.print("Status = ");
    Serial.println(Status);
    Serial.println("-----------------------------------------------------");
  */
}
