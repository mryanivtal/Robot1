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

void Behavior::setBehavior(TimebasedAction** actionListP, byte actionCountP)
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

//	//LOG****************************************************************************
//		Serial.print("Behavior.run - entered if statement, time to execute an action.  millis=  ");	//LOG
//		Serial.print(millis());																		//LOG
//		Serial.print("behaviorNextActionTime=  ");													//LOG
//		Serial.println(behaviorNextActionTime);														//LOG
//	//LOG****************************************************************************

		behaviorLastActionTime=millis();
		nextAction->execute();
		updateNextAction();
	}
	lastRunTime=behaviorLastActionTime;
}

void Behavior::updateNextAction()
{

//	Serial.print("Entered Behavior::updateNextAction().  millis=  ");							//LOG
//	Serial.print(millis());																		//LOG
//	Serial.print(".    actionCount= ");															//LOG
//	Serial.println(actionCount);																//LOG

	unsigned long minimal=MAX_ULONG;
	unsigned long x=0;
	TimebasedAction** T=actionList;
	for(byte i=0; i<actionCount; i++)
	{
//		Serial.print("Inside for statement.  i=");												//LOG
//		Serial.print(i);																		//LOG
//		Serial.print(", T[i]->getNextActionTime()= ");											//LOG
//		Serial.println(T[i]->getNextActionTime());												//LOG

		x = T[i]->getNextActionTime();

//		Serial.print("x=");																		//LOG
//		Serial.print(x);																		//LOG
//		Serial.print(", minimal=");																//LOG
//		Serial.println(minimal);																//LOG

		if(x <= minimal)
		{
			minimal=x;
			nextAction=T[i];
		}
		behaviorNextActionTime=minimal;
	}
}



} /* namespace Behavior_ns */
