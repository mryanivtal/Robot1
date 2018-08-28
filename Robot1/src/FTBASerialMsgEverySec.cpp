/*
 * FTBASerialMsgEverySec.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include <FTBASerialMsgEverySec.h>
#include <Log.h>

using namespace Log_NS;

namespace Behavior_ns {

FTBA_SerialMsgEverySec::FTBA_SerialMsgEverySec(unsigned long delayInMillis, Log* LP)
 : FixedTimebasedAction(delayInMillis)
{
	 L = LP;
}

FTBA_SerialMsgEverySec::~FTBA_SerialMsgEverySec()
{
}


void FTBA_SerialMsgEverySec::doYourThing(void)
{
	L->println("Ping! ");
}



} /* namespace Behavior_ns */

