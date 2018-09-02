/*
 * Wheel.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: yaniv
 */

#include "Wheel.h"
#include <Arduino.h>

namespace Movement_NS {

Wheel::Wheel() {
}

Wheel::~Wheel() {
}

void Wheel::begin(byte motorPinAP, byte motorPinBP, byte motorPinPWMP, bool motorFwdPolarityP, int motorPWMToRPMP, int wheelDiameterInMmP) {

	motor.begin(motorPinAP, motorPinBP, motorPinPWMP, motorPWMToRPMP, motorFwdPolarityP);
	setWheelSize(wheelDiameterInMmP);
}

void Wheel::setWheelSize(int diameterInMmP) {
	wheelDiameterInMm=diameterInMmP;
	RPMToMmSec=wheelDiameterInMm*3.1415927;
}

void Wheel::setWheelSpeed(int speedInMmPerMinP) {
	speedInMmPerMin=speedInMmPerMinP;
	int speedInRPM=speedInMmPerMin/RPMToMmSec;
	motor.setMotorSpeed(speedInRPM);				//calculate required RPM per speed value
}

int Wheel::getWheelSpeed(void) {
	return(speedInMmPerMin);
}

int Wheel::getWheelSize(void) {
	return(wheelDiameterInMm);
}

} /* namespace Movement_NS */
