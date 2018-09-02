/*
 * WheelPair.h
 *
 *  Created on: Sep 3, 2018
 *      Author: yaniv
 */

#ifndef SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_
#define SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_

#include "Wheel.h"

namespace Movement_NS {

class WheelPair {
public:
	WheelPair();
	virtual ~WheelPair();

	void Turn(float angle, float turnRadius);
	void drive(Direction dir, int speedInMmPerMin);


};

} /* namespace Movement_NS */

#endif /* SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_ */
