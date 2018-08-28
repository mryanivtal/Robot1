/*
 * Log.h
 * This class abstracts the Serial logging functionality for future uses
 * the implementation is in the h file due to template imlementation
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#ifndef SRC_LOG_H_
#define SRC_LOG_H_

#define LOGGING_MODE				//Parameter to define if need to log to serial.  if not, comment this line
#define SERIAL_SPEED 115200			//Serial port comm speed.

#include <Arduino.h>


namespace Log_NS {

//********************************************* Log Class declaration - abstraction for logging
class Log
{
public:
	Log();
	virtual ~Log();

	void print(const char* s);
	void println(const char* s);
	void print(unsigned long s);
	void println(unsigned long s);

private:
	void init(void);

};

}; /* namespace Log_NS */

#endif /* SRC_LOG_H_ */

