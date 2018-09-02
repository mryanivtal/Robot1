/*
 * Motor.h
 *
 *  Created on: Sep 2, 2018
 *      Author: yaniv
 */

#ifndef SRC_MOTORS_HBRIDGE_L298N_MOTOR_H_
#define SRC_MOTORS_HBRIDGE_L298N_MOTOR_H_

#include <Arduino.h>


namespace Movement_NS {

typedef enum Direction {
	FWD=1,
	BWD=0
} Direction;


class Motor {
public:
	Motor();
	virtual ~Motor();

	void begin(byte pinAP, byte pinBP, byte pinPWMP, int PWMToRPMP, bool motorFwdPolrityP);		//begin - set motor (PWM value/RPM) constant

	void setMotorSpeed(int SpeedInRPMP);		//update motor speed in RPM
	void setDirection(Direction directionP); 	//set direction

	int getSpeed(void);
	Direction getDirection(void);

protected:
	byte pinA=0, pinB=0, pinPWM=0;
	int PWMToRPM=0;
	bool motorFwdPolrity=0;

	Direction motorDirection=FWD;
	int motorSpeed=0;

};

} /* namespace Movement_NS */

#endif /* SRC_MOTORS_HBRIDGE_L298N_MOTOR_H_ */
