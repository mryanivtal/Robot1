/*
 * FixedTimebasedAction.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include <FixedTimebasedAction.h>
#include <Arduino.h>

namespace Behavior_ns {

FixedTimebasedAction::FixedTimebasedAction(unsigned long delayInMillisP)
{
	delayInMillis=delayInMillisP;
	calcNextActionTime();
}

FixedTimebasedAction::~FixedTimebasedAction()
{
	// TODO Auto-generated destructor stub
}

void FixedTimebasedAction::calcNextActionTime(void)
{
	nextActionTime=millis()+delayInMillis;
}

void FixedTimebasedAction::execute(void)
{
	lastActionTime=millis();
	calcNextActionTime();
	doYourThing();
}


} /* namespace Behavior_ns */
