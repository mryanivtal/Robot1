/*
 * FixedTimebasedAction.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include <FixedTimebasedAction.h>
#include <Arduino.h>

namespace Behavior_ns {

FixedTimebasedAction::FixedTimebasedAction()
{
}

FixedTimebasedAction::~FixedTimebasedAction()
{
	// TODO Auto-generated destructor stub
}

void FixedTimebasedAction::setDelay(unsigned long delayInMillisP)
{
	delayInMillis=delayInMillisP;
	calcNextActionTime();
}
void FixedTimebasedAction::calcNextActionTime(void)
{
	nextActionTime=millis()+delayInMillis;
}

void FixedTimebasedAction::execute(void)
{
	Serial.println("entered FixedTimebasedAction::execute");			//LOG"
	delay(500);															//LOG

	lastActionTime=millis();
	calcNextActionTime();
	doYourThing();
}


} /* namespace Behavior_ns */
