#include "Datalog.h"
#include <SD.h>

Datalog::Datalog(String filename, int lograte){
	buffer = "";
	const byte chipSelect = 10;
	logtime = lograte;
	
	filename.trim();
	filename.replace(" ", "_");
	filename = filename + "00.txt";
	
	byte dzlen = filename.length() - 6;
	
	
	Serial.begin(9600);
	
	if(!SD.begin(chipSelect)){
		Serial.println("Card failed. Cannot initialize.");
		return;
	}
	Serial.print("Card initialized, creating file ");
	char *filenameChar=&filename[0];//might create issues converting strings to chars here
	for(uint8_t i = 0; i < 100; i++){
		filenameChar[dzlen] = i/10 + '0';
		filenameChar[dzlen - 1] = i%10 + '0';
		if(!SD.exists(filenameChar)){
			logf = SD.open(filenameChar, O_CREAT | O_APPEND | O_WRITE);
			finalName = filenameChar;
			break;
		}
	}
	if(!logf){
    error("Couldn't create file");
    }
	
}
/*
void Datalog::addData(int intdata){
	buffer += intdata;
	buffer += ", ";
}
*/
/*
void Datalog::addData(short shortdata){
	buffer += shortdata;
	buffer += ", ";
}
*/
//last two might be redundant (if you can plug shorts and ints into longs)

void Datalog::addData(long longdata){
	buffer += longdata;
	buffer += ", ";
}

void Datalog::addData(String stringdata){
	buffer += stringdata;
	buffer += ", ";
}
/*
void Datalog::addData(float floatdata){
	String tempstring = decToString(floatdata);
	buffer += tempstring;
	buffer += ", ";
	tempstring = "";
}
*/
void Datalog::addData(double doubledata){
	String tempstring = decToString(doubledata);
	buffer += tempstring;
	buffer += ", ";
	tempstring = "";
}
/*
String Datalog::decToString(float tempfloat){
	char[15] charVal2;
	String ftempstring = "";
  
	dtostrf(tempfloat, 3, 3, charVal);
	for(int i=0;i<sizeof(charVal);i++){
		ftempstring += charVal[i];
	}
	ftempstring.trim();
	return ftempstring;
}
*/
String Datalog::decToString(double tempdouble){
	char charVal2[15];
	String dtempstring = "";
  
	dtostrf(tempdouble, 3, 3, charVal2);
	for(int i=0;i<sizeof(charVal2);i++){
		dtempstring += charVal2[i];
	}
	dtempstring.trim();
	return dtempstring;
}

void Datalog::error(String errorString){
	Serial.println(errorString);
	pinMode(13, OUTPUT);
	digitalWrite(13, 255);
	while(1);
  return;
}

void Datalog::flushData(){
  char *charbuff=&buffer[0];
	
        if(logf){
		logf.write(charbuff);
		logf.flush();
	}
  return; 
}
