/*
* Arduino Wireless Communication Tutorial
*     Example 1 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(19, 20); // CE, CSN
const byte address[6] = "00001";
double wave;
int i=0;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {

  while(i<20)
  {
    delay(2);
    wave=cos(3.14159*2.0*200.0*i*0.002);
    ++i;
    radio.write(&wave, sizeof(wave));
    //Serial.println(wave);
  }
  i=0;
}
