#ifndef Datalog_h
#define Datalog_h 
#include <SD.h>

class Datalog{
	public:
		Datalog(String filename, int lograte);
		void addData(long longdata);
		void addData(String stringdata);
		void addData(char);
		void addData(double doubledata);
		void flushData();
		void closeFile();
		String buffer;
		int logtime;
		File logf;
		
	private:
		String decToString(double tempdouble);
		void error(String errorString);
		int lastLog;
		String finalName;
};
#endif