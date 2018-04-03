#include <SoftwareSerial.h>

int Rx=4,Tx=3; 
int d;
signed long Volt;
SoftwareSerial mySerial =  SoftwareSerial(Rx, Tx);

 
void setup()  {
  Serial.begin(2000000);
 // Serial.println("Wireless Seismic Acquisition, Serial Communication is ON");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  //mySerial.println("Hello, Reciever is talking");
}
 
 
 
void loop()                     // run over and over again
{
 
  if (mySerial.available()) {
  
     d=mySerial.read();
     if(d>47 && d<58){
      
      Serial.print(d-48);
     }
     else Serial.println(" ");
  
 }
  
 }
