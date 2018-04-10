#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

const int Rx = 4, Tx = 3, SD_CS = 6;
int d;

SoftwareSerial mySerial =  SoftwareSerial(Rx, Tx);
File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(2000000);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Communication Part
  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);

  //SD part up to end of the setup
  Serial.print("Initializing SD card...");

  if (!SD.begin(SD_CS)) {
    Serial.println("initialization failed! The device is niether recieving or recording any thing!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("Recieved_Data.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Recording Data...");
    myFile.println("Recording Data...");
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {

  if (mySerial.available()) {//communication

    d = mySerial.read(); //Read Recieved Data           //communication

    if (d > 47 && d < 58) { //if d in the range of numbers in ASCII       //communication

      Serial.print(d - 48);  //print data to serial monitor               //communication

      // re-open the file in SD for recording
      myFile = SD.open("Recieved_Data.txt", FILE_WRITE);                                  //SD start
      if (myFile) {                                                                       //
        myFile.print(d - 48);                                                             //
        // close the file:                                                                //
        myFile.close();                                                                   //                           
      }                                                                                   //
      else {                                                                              //
        // if the file didn't open, print an error:                                       //
        Serial.println("error opening Recieved_Data.txt, this number was not recorded");  //SD ends
      }
    }

    else {                    //communication
      Serial.println(" ");    //communication

      // re-open the file in SD for recording                                            //SD start
      myFile = SD.open("Recieved_Data.txt", FILE_WRITE);                                 //
      if (myFile) {                                                                      //
        myFile.println(" ");                                                             //
        // close the file:                                                               //
        myFile.close();                                                                  //
      }                                                                                  //
      else {                                                                             //
        // if the file didn't open, print an error:                                      //
        Serial.println("error opening Recieved_Data.txt, Couldn't enter a new line");    //SD ends
      }
    }
  }
}
