/*
 * TBASSerialWrite.cpp
 *
 *  Created on: Aug 28, 2018
 *      Author: yaniv
 */

#include "../ActionClasses/SerialWrite.h"

namespace TimeBasedActionSet_NS {

SerialWrite::SerialWrite()
{
}

SerialWrite::~SerialWrite()
{
}

void SerialWrite::setMsg(String msgP)
{
	msg=msgP;
}

void SerialWrite::display(void)
{
	Serial.println(msg);
}

} /* namespace TimeBasedActionSet_NS */
