/*
 * Behavior.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#define MAX_ULONG 4294967295

#include <Behavior.h>

namespace Behavior_ns {

Behavior::Behavior()
{
}

Behavior::~Behavior()
{
	// TODO Auto-generated destructor stub
}

void Behavior::setBehavior(TimebasedAction* actionListP, byte actionCountP)
{
	actionList=actionListP;
	actionCount=actionCountP;
	startTime=millis();

	updateNextAction();
}


void Behavior::run(void)
{
	if(behaviorNextActionTime <= millis())
	{
		Serial.print("Behavior.run - entered if statement, time to execute an action.  millis is ");	//LOG
		Serial.println(millis());			//LOG
		delay(500);							//LOG

		nextAction->execute();
		updateNextAction();
		behaviorLastActionTime=millis();
	}
	lastRunTime=millis();
}

void Behavior::updateNextAction()
{
	unsigned long minimal=MAX_ULONG;
	unsigned long x=0;
	TimebasedAction* T=0;
	for(byte i=0; i<actionCount; i++)
	{
		T = actionList + i*sizeof(TimebasedAction);
		x = T->getNextActionTime();
		if(x <= minimal)
		{
			minimal=x;
			nextAction=T;
		}
	}
}



} /* namespace Behavior_ns */
