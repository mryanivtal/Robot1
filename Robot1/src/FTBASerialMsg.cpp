/*
 * FTBASerialMsgEverySec.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include "FTBASerialMsg.h"

#include <Arduino.h>
#include "FixedTimebasedAction.h"

namespace Behavior_ns {

FTBA_SerialMsg::FTBA_SerialMsg()
{
}

FTBA_SerialMsg::~FTBA_SerialMsg()
{
}

void FTBA_SerialMsg::init(unsigned long delayInMillisP, String msgP)
{
	setDelay(delayInMillisP);
	msg=msgP;
}
void FTBA_SerialMsg::doYourThing(void)
{
	Serial.println(msg);
}



} /* namespace Behavior_ns */
