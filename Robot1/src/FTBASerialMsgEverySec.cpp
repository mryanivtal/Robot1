/*
 * FTBASerialMsgEverySec.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include <Arduino.h>
#include <FTBASerialMsgEverySec.h>

namespace Behavior_ns {

FTBA_SerialMsgEverySec::FTBA_SerialMsgEverySec(unsigned long delayInMillis)
 : FixedTimebasedAction(delayInMillis)
{
}

FTBA_SerialMsgEverySec::~FTBA_SerialMsgEverySec()
{
}


void FTBA_SerialMsgEverySec::doYourThing(void)
{
	Serial.println("Ping! ");
}



} /* namespace Behavior_ns */

