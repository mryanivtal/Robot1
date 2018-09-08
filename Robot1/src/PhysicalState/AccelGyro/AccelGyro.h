/*
 * AccelGyro.h
 *
 *  Created on: Aug 31, 2018
 *      Author: yaniv
 */


// run() measurement - 2-3 millis including 3 serial writes

#include <Arduino.h>
#include <Wire.h>

#ifndef SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_
#define SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_

#define GY521_ADDR 0x68				// I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69
#define GY521_CALIBRATE_GYRO_X -3200		//specific board calibration numbers
#define GY521_CALIBRATE_GYRO_Y -280
#define GY521_CALIBRATE_GYRO_Z -526

#define GY521_CALIBRATE_ACCL_X -500		//specific board calibration numbers
#define GY521_CALIBRATE_ACCL_Y 500
#define GY521_CALIBRATE_ACCL_Z 2500

// treasholds and mva values - can be calibrated
#define MVA_FOR_ORIENTATION 20		//moving avg power for orientation estimation

#define MVA_FOR_AT_REST 5			//moving avg power for atRest estimation
#define DIFF_TRESHOLD_FOR_AT_REST 200	// how much value change can we attribute for noise
#define CYCLES_FOR_AT_REST 4		// how many measurements with no movement before atRest updates



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
	void updateAtRest(void);			// update atRest based on sensor data
	void updateAll(void);				//update ALL calculated params based on sensor raw data.


	Orientation getSensorOrientation(void);		//return sensor orientation

//TODO:
//	bool isTilted(void);				//is the sensor being tilted
//	bool isFlying(void)					//is the sensor under high linear acceleration
	bool isAtRest(void);				//is the sensor put down

protected:
	const int MPU_ADDR=GY521_ADDR; 			// I2C address of the MPU-6050 (HW parameter)
	const int GYRO_CALIBRATION[3] = {GY521_CALIBRATE_GYRO_X, GY521_CALIBRATE_GYRO_Y, GY521_CALIBRATE_GYRO_Z};	//gyro calibration deltas
	const int ACCL_CALIBRATION[3] = {GY521_CALIBRATE_ACCL_X, GY521_CALIBRATE_ACCL_Y, GY521_CALIBRATE_ACCL_Z};	//Accelerometer calibration deltas


	int16_t accelRawData[3]; 	// vector for accelerometer raw data [x,y,z]
	int16_t gyroRawData[3]; 	// vector for gyro raw data
	int16_t temperature=0; 		// variables for temperature data

	long mvaOrientationAccel[3];       //moving average vector [x,y,z] of acceleration for orientation estimation (Gravity based)
	Orientation sensorOrientation=(Orientation)1;		//sensor orientation

	long mvaAtRest[6];					//moving avg vector [accelX, accY, accZ, GyroX, GyroY, GyroZ] for at rest estimation
	unsigned int atRestCycles=0;
	bool atRest=1;						//is the sensor at Rest for defined no of cycles?


	bool tilted=0;						//is the sensor being tilted
	bool flying=0;						//is the sensor under continuous high linear acceleration

};

} /* namespace PhysicalState_NS */

#endif /* SRC_PHYSICALSTATE_ACCELGYRO_ACCELGYRO_H_ */
