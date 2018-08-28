/*
 * TimebasedAction.cpp
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#include "TimebasedAction.h"

namespace Behavior_ns {


unsigned long TimebasedAction::getNextActionTime(void)
{
	return(nextActionTime);
}


} /* namespace Behavior_ns */


