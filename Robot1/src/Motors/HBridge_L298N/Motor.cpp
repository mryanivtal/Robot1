/*
 * Motor.cpp
 *
 *  Created on: Sep 2, 2018
 *      Author: yaniv
 */

#include "Motor.h"

namespace Movement_NS {

Motor::Motor() {
}

Motor::~Motor() {
}

void Motor::begin(byte pinAP, byte pinBP, byte pinPWMP, int PWMToRPMP, bool motorFwdPolrityP) {

	pinA=pinAP;
	pinB=pinBP;
	pinPWM=pinPWMP;
	PWMToRPM=PWMToRPMP;
	motorFwdPolrity=motorFwdPolrityP;

	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(pinPWM, OUTPUT);

	setMotorSpeed(0);
	setDirection(FWD);
}

void Motor::setMotorSpeed(int SpeedInRPMP) {
	analogWrite(pinPWM, motorSpeed*PWMToRPM);
}

void Motor::setDirection(Direction directionP) {
	if(motorDirection==FWD) {
		if(motorFwdPolrity==0) {
	    digitalWrite(pinA, HIGH);
	    digitalWrite(pinB, LOW);
		}
		else {
			digitalWrite(pinA, LOW);
			digitalWrite(pinB, HIGH);
		}
	}
	else {			//if(motorDirection==BWD)
		if(motorFwdPolrity==0) {
			digitalWrite(pinA, LOW);
			digitalWrite(pinB, HIGH);
		}
		else {
			digitalWrite(pinA, HIGH);
			digitalWrite(pinB, LOW);
		}
	}
}

int Motor::getSpeed(void) {
	return(motorSpeed);
}

Direction Motor::getDirection(void) {
	return(motorDirection);
}

} /* namespace Movement_NS */
