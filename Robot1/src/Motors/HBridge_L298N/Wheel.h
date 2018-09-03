/*
 * Wheel.h
 *
 *  Created on: Sep 2, 2018
 *      Author: yaniv
 */

#ifndef SRC_MOTORS_HBRIDGE_L298N_WHEEL_H_
#define SRC_MOTORS_HBRIDGE_L298N_WHEEL_H_

#include <Arduino.h>
#include "Motor.h"

namespace Movement_NS {

class Wheel {
public:
	Wheel();
	virtual ~Wheel();

	void begin(byte motorPinAP, byte motorPinBP, byte motorPinPWMP, bool motorFwdPolarityP, int motorPWMToRPMP, int wheelDiameterInMmP);

	void setWheelSpeed(int speedInMmPerMinP);

	int getWheelSpeed(void);
	int getWheelSize(void);

protected:
	Motor motor;

	float RPMToMmSec=0;
	int speedInMmPerMin;
	int wheelDiameterInMm;
	void setWheelSize(int diameterInMmP);
};

} /* namespace Movement_NS */

#endif /* SRC_MOTORS_HBRIDGE_L298N_WHEEL_H_ */
