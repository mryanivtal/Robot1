/*
 * Behavior.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_BEHAVIOR_H_
#define SRC_BEHAVIOR_H_

#include <Arduino.h>
#include "TimebasedAction.h"

namespace Behavior_ns {

class Behavior {

public:
	Behavior(TimebasedAction* actionListP, byte actionCountP);
	virtual ~Behavior();

	void run();
	void setBehavior(TimebasedAction* actionListP, byte actionCountP);

private:
	void updateNextAction();

	unsigned long startTime=0;				//time object was initiated
	unsigned long lastRunTime=0;			//last time Run function was executed
	unsigned long behaviorLastActionTime=0;		//last time an action was executed
	unsigned long behaviorNextActionTime=0;		//next time an action should be executed

	TimebasedAction* actionList=0;		//pointer to linked list of actions
	byte actionCount=0;
	TimebasedAction* nextAction=0;		//pointer to action to run next
};

} /* namespace Behavior_ns */

#endif /* SRC_BEHAVIOR_H_ */
