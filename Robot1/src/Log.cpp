/*
 * Log.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: yaniv
 */

#define LOGGING_MODE				//Parameter to define if need to log to serial.  if not, comment this line
#define SERIAL_SPEED 115200			//Serial port comm speed.

#include <Arduino.h>
#include "Log.h"


namespace Log_NS {


Log::Log()
{
	// TODO Auto-generated constructor stub
	init();
};

Log::~Log()
{
	// TODO Auto-generated destructor stub
}

void Log::init(void)		//Start serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.begin(SERIAL_SPEED);	//initiate serial
		while(!Serial);			//Wait till available
		this->print("Serial initiated at ");
		this->println(SERIAL_SPEED);
	#endif
};

void Log::print(const char *s)			//print to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.print(s);
	#endif
};

void Log::println(const char* s)		//println to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.println(s);
	#endif
}

void Log::print(unsigned long s)			//print to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.print(s);
	#endif
};

void Log::println(unsigned long s)		//println to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.println(s);
	#endif
}
//*************************************************************************************
}; /* namespace Log_NS */

