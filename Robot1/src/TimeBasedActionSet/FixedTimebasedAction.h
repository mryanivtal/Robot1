/*
 * FixedTimebasedAction.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_FIXEDTIMEBASEDACTION_H_
#define SRC_FIXEDTIMEBASEDACTION_H_

#include "../TimeBasedActionSet/TimebasedAction.h"

namespace TimeBasedActionSet_NS {

class FixedTimebasedAction: public TimebasedAction {
public:
	FixedTimebasedAction();
	virtual ~FixedTimebasedAction();
	void setDelay(unsigned long delayInMillis);

protected:
	void calcNextActionTime(void);
	unsigned long delayInMillis=0;
	void execute(void);
	virtual void doYourThing(void)=0;



};

} /* namespace Behavior_ns */

#endif /* SRC_FIXEDTIMEBASEDACTION_H_ */
