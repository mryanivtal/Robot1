/*
 * Behavior.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_BEHAVIOR_H_
#define SRC_BEHAVIOR_H_

#include <Arduino.h>

#include "../TimeBasedActionSet/TimebasedAction.h"

namespace TimeBasedActionSet_NS {

class TimeBasedActionSet {

public:
	TimeBasedActionSet();
	virtual ~TimeBasedActionSet();

	void run();
	void setBehavior(TimebasedAction** actionListP, byte actionCountP);

protected:
	void updateNextAction();

	unsigned long startTime=0;				//time object was initiated
	unsigned long lastRunTime=0;			//last time Run function was executed
	unsigned long behaviorLastActionTime=0;		//last time an action was executed
	unsigned long behaviorNextActionTime=0;		//next time an action should be executed

	TimebasedAction** actionList=0;		//pointer to array of pointers to TimebasedAction
	byte actionCount=0;					// No. of active entities in array
	TimebasedAction* nextAction=0;		//pointer to action to run next
};

} /* namespace Behavior_ns */

#endif /* SRC_BEHAVIOR_H_ */
