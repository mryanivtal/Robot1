/*
 * FixedTimebasedAction.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_FIXEDTIMEBASEDACTION_H_
#define SRC_FIXEDTIMEBASEDACTION_H_

#include <TimebasedAction.h>

namespace Behavior_ns {

class FixedTimebasedAction: public TimebasedAction {
public:
	FixedTimebasedAction(unsigned long delayInMillis);
	virtual ~FixedTimebasedAction();

	void execute(void);
	virtual void doYourThing(void)=0;

private:
	void calcNextActionTime(void);
	unsigned long delayInMillis=0;
};

} /* namespace Behavior_ns */

#endif /* SRC_FIXEDTIMEBASEDACTION_H_ */
