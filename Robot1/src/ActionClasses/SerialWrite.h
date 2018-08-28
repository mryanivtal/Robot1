/*
 * TBASSerialWrite.h
 *
 *  Created on: Aug 28, 2018
 *      Author: yaniv
 */

#include <Arduino.h>

#ifndef SRC_TIMEBASEDACTIONSET_TBASSERIALWRITE_H_
#define SRC_TIMEBASEDACTIONSET_SERIALWRITE_H_

namespace TimeBasedActionSet_NS {

class SerialWrite {
public:
	SerialWrite();
	virtual ~SerialWrite();

	void setMsg(String msgP);
	void display(void);


protected:
	String msg;
};

} /* namespace TimeBasedActionSet_NS */

#endif /* SRC_TIMEBASEDACTIONSET_SERIALWRITE_H_ */
