/*
 * FTBASerialMsgEverySec.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include <Arduino.h>
#include "FTBASerialMsgEverySec.h"
#include "FixedTimebasedAction.h"

namespace Behavior_ns {

FTBA_SerialMsgEverySec::FTBA_SerialMsgEverySec()
{
}

FTBA_SerialMsgEverySec::~FTBA_SerialMsgEverySec()
{
}

void FTBA_SerialMsgEverySec::init(unsigned long delayInMillisP, String msgP)
{
	setDelay(delayInMillisP);
	msg=msgP;
}
void FTBA_SerialMsgEverySec::doYourThing(void)
{
	Serial.println(msg);
}



} /* namespace Behavior_ns */

