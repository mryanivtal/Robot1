/*
 * TimebasedAction.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_TIMEBASEDACTION_H_
#define SRC_TIMEBASEDACTION_H_

namespace TimeBasedActionSet_NS {

class TimebasedAction {
public:
	TimebasedAction();
	virtual ~TimebasedAction();

	unsigned long getNextActionTime(void);		//return next action execution time
	virtual void execute(void)=0;				//Execute this action

protected:
	unsigned long lastActionTime=0;				//last time this action was executed
	unsigned long nextActionTime=0;				//next time to execute this action (in millis)
	virtual void calcNextActionTime(void)=0;	//calculate next execution time
	virtual void doYourThing(void)=0;

};

} /* namespace Behavior_ns */

#endif /* SRC_TIMEBASEDACTION_H_ */
