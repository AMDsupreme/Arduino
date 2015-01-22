#include "SD.h"
#include <Wire.h>
#include "RTClib.h"

#define LOG_INTERVAL 10
#define ECHO_TO_SERIAL 0
#define WAIT_TO_START 5

const int CSPin = 0, chipSelect = 10, redLEDpin = 3, greenLEDpin = 4;
float CSraw, CSVal, CSvolt;

File logfile;

void setup(){
  Serial.begin(115200);

#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif

  Serial.println("Initializing SD card...");

  pinMode(10, OUTPUT);

  if (!SD.begin(chipSelect)){
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initialized, creating file...");

  char filename[] = "LOGGER00.txt";
  for(uint8_t i = 0; i < 100; i++){
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if(!SD.exists(filename)){
      logfile = SD.open(filename, FILE_WRITE);
      break;
    }
  }

  if(!logfile){
    error("Couldn't create file");
    }
  else{
  }

  logfile.println("millis,CSVal,CSvolt");    
#if ECHO_TO_SERIAL
  Serial.println("millis,CSVal,CSvolt");
#endif
  
  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

  Serial.print("Logging current sensor data to: ");
  Serial.println(filename);

  uint32_t m = millis();
  logfile.print(m);
  logfile.print(", ");
#if ECHO_TO_SERIAL
  Serial.print(m);
  Serial.print(", ");
#endif
}

void loop(){
  delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));

  uint32_t m = millis();
  logfile.print(m);
  logfile.print(", ");
#if ECHO_TO_SERIAL
  Serial.print(m);
  Serial.print(", ");
#endif


  CSraw = analogRead(CSPin);
  CSvolt = CSraw * (5.000/1023.000);
  CSVal = ((CSvolt - 2.500) / .0660);
  Serial.print("Current: "); 
  Serial.print(CSVal); 
  Serial.print("\t");
  Serial.print("Voltage: "); 
  Serial.println(CSvolt);

  logfile.print(CSVal);
  logfile.print(", ");
  logfile.println(CSvolt);
    delay(5);
}




void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}


