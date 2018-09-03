/*
 * WheelPair.h
 *
 *  Created on: Sep 3, 2018
 *      Author: yaniv
 */

#ifndef SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_
#define SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_

#include <Arduino.h>
#include "Wheel.h"

namespace Movement_NS {

class WheelPair {
public:
	WheelPair();
	virtual ~WheelPair();

	void begin(Wheel *wheelLP, Wheel *wheelRP, float distBetweenWheelsMmP);

	void Turn(float angle, float turnRadius);
	void drive(Direction dir, int speedInMmPerMin);

protected:
	Wheel *wheelL=0, *wheelR=0;
	float distBetweenWheelsMm=0;
	int speedInMmPerMin;
	Direction direction=FWD;






};

} /* namespace Movement_NS */

#endif /* SRC_MOTORS_HBRIDGE_L298N_WHEELPAIR_H_ */
