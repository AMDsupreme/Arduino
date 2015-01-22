#ifndef Datalog_h
#define Datalog_h 
#include <SD.h>

class Datalog{
	public:
		datalog(String, int);
		void addData(int);
		void addData(short);
		void addData(long);
		void addData(String);
		void addData(char);
		void addData(float);
		void addData(double);
		void flush();
		void closeFile();
		void onlyWrite(String);
		void onlyWrite(double);
		void onlyWrite(long);
		String buffer;
		int logtime;
		
	private:
		String decToString(float);
		String decToString(double);
		void error(String);
		int lastLog;
		String finalName
};
#endif