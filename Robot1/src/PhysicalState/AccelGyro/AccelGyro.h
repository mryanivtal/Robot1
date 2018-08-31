/*
 * AccelGyro.h
 *
 *  Created on: Aug 31, 2018
 *      Author: yaniv
 */

#include <Arduino.h>
#include <Wire.h>

#ifndef SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_
#define SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_

#define GY521_ADDR 0x68				// I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69
#define GY521_CALIBRATE_X -3200		//specific board calibration numbers
#define GY521_CALIBRATE_Y -280
#define GY521_CALIBRATE_Z -526

#define MVA_FOR_ORIENTATION 20


namespace PhysicalState_NS {

typedef enum Orientation {		//Which side points up!
	XPos=1,
	XNeg=-1,
	YPos=2,
	YNeg=-2,
	ZPos=3,
	ZNeg=-3
} Orientation;


class AccelGyro {
public:
	AccelGyro();
	virtual ~AccelGyro();

	void begin(void);					// init board
	void sampleSensor(void);			//update data from sensor
	void updateOrientation(void);		//update orientation based on sensor raw data.
	void updateStatus(void);			//update ALL calculated params based on sensor raw data.


	Orientation getSensorOrientation(void);		//return sensor orientation

//TODO:
//	bool isTilted(void);				//is the sensor being tilted
//	bool isFlying(void)					//is the sensor under high linear acceleration
//	bool isNotMoving(void);				//is the sensor put down

protected:
	const int MPU_ADDR=GY521_ADDR; 			// I2C address of the MPU-6050 (HW parameter)
	const int GYRO_CALIBRATION[3] = {GY521_CALIBRATE_X, GY521_CALIBRATE_Y, GY521_CALIBRATE_Z};	//gyro calibration deltas

	int16_t accelRawData[3]; 	// vector for accelerometer raw data [x,y,z]
	int16_t gyroRawData[3]; 	// vector for gyro raw data
	int16_t temperature=0; 		// variables for temperature data

	long mvaOrientationAccel[3];       //moving average vector [x,y,z] of acceleration measurements


	Orientation sensorOrientation=(Orientation)1;		//sensor orientation
	bool isTilted=0;						//is the sensor being tilted
	bool isFlying=0;						//is the sensor under continuous high linear acceleration
	bool isNotMoving=0;						//is the sensor put down

};

} /* namespace PhysicalState_NS */

#endif /* SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_ */
