/*
 * Log.h
 * This class abstracts the Serial logging functionality for future uses
 * the implementation is in the h file due to template imlementation
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define LOGGING_MODE				//Parameter to define if need to log to serial.  if not, comment this line
#define SERIAL_SPEED 115200

#include <Arduino.h>

namespace Log_NS {


//********************************************* Class header
class Log {
public:
	Log();
	virtual ~Log();

	template <class T> void print(T s);
	template <class T> void println(T s);

private:
	void init(void);

};

//**********************************************Class functions (Templetized to match Serial input params)
Log::Log() {
	// TODO Auto-generated constructor stub
	init();

};

Log::~Log() {
	// TODO Auto-generated destructor stub
}

}; /* namespace Log_NS */


void Log_NS::Log::init(void)		//Start serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.begin(SERIAL_SPEED);	//initiate serial
		while(!Serial);			//Wait till available
		this->print("Serial initiated at ");
		this->println(SERIAL_SPEED);
	#endif
};

template <class T> void Log_NS::Log::print(T s)			//print to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.print(s);
	#endif
};

template <class T> void Log_NS::Log::println(T s)		//println to serial if in logging mode, else do nothing
{
	#ifdef LOGGING_MODE			//Logging mode?
		Serial.println(s);
	#endif
}

