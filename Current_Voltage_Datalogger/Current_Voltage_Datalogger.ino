

#include <SD.h>

// On the Ethernet Shield, CS is pin 4. Note that even if it's not
// used as the CS pin, the hardware CS pin (10 on most Arduino boards,
// 53 on the Mega) must be left as an output or the SD library
// functions will not work.
const int chipSelect = 10, CSPin = 0;
float CSraw, CSval, CSvolt;
//all of these variables are declared here so they can be used throughout the code
void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  // make a string for assembling the data to log:
  String dataString = "";
  char charVal[5], charVal2[5];
  String svolt, sval;
  // read three sensors and append to the string:
  int m = millis();
  dataString += String(m);
  dataString += ", ";
  
  CSraw = analogRead(CSPin);
  CSvolt = CSraw * (5.000/1023.000);
  CSval = ((CSvolt - 2.500) / .0660); //analog in to current and voltage
  
  dtostrf(CSval, 4, 2, charVal);
 
  for(int i=0;i<sizeof(charVal);i++){
    sval+=charVal[i];
  } //this converts floats to strings
  
  dtostrf(CSvolt, 4, 2, charVal2);
  for(int i=0;i<sizeof(charVal2);i++){
    svolt+=charVal2[i];
  } //this converts floats to strings  
  
  dataString += sval;
  dataString += ", ";
  dataString += svolt;
  

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
  delay(100);
}
