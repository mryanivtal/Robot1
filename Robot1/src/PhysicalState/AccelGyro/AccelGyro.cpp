/*
 * AccelGyro.cpp
 *
 *  Created on: Aug 31, 2018
 *      Author: yaniv
 */

#include "AccelGyro.h"

namespace PhysicalState_NS {

AccelGyro::AccelGyro() {
}

AccelGyro::~AccelGyro() {
}

void AccelGyro::begin(void) {
	Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
	Wire.write(0x6B); // PWR_MGMT_1 register
	Wire.write(0); // set to zero (wakes up the MPU-6050)
	Wire.endTransmission(true);
}

void AccelGyro::sampleSensor(void) {

	int i;

	Wire.beginTransmission(MPU_ADDR);
	Wire.write(0x3B); 				// starting with register 0x3B (ACCEL_XOUT_H)
									//[MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
	Wire.endTransmission(false); 	// the parameter indicates that the Arduino will send a restart.
									// As a result, the connection is kept active.
	Wire.requestFrom(MPU_ADDR, 7 * 2, true); 	// request a total of 7*2=14 registers

	for (i = 0; i < 3; i++) {
		accelRawData[i] = Wire.read() << 8 | Wire.read(); 	// reading two registers each time - accel data
	}

	temperature = Wire.read() << 8 | Wire.read(); 			// reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)

	for (i = 0; i < 3; i++) {
		gyroRawData[i] = Wire.read() << 8 | Wire.read(); 	// reading two registers each time - gyro data
	}

	for (i = 0; i < 3; i++) {								// Calibrate gyro data
		gyroRawData[i] += GYRO_CALIBRATION[i];
	}

}

void AccelGyro::updateOrientation(void) {
	  //Calculate estimated sensor orientation - biggest absolute value of slow moving avg or linear accelerometer

	  int a=0, b=0, c=0, i;

	  for(i=0; i<3; i++) {								//Moving average for orientation estimation
		  mvaOrientationAccel[i] = (mvaOrientationAccel[i]*(MVA_FOR_ORIENTATION-1) + accelRawData[i])/MVA_FOR_ORIENTATION;
		  if(abs(mvaOrientationAccel[i]) > abs(b)) {
			  a=i;									//a indicates the axis (0=x, 1=y, 2=z)
			  b=mvaOrientationAccel[i];				//b holds the actual value to indicate direction (pos/neg)
		  }
	  }

	  if (b>=0) c=1; else c=-1;
	  sensorOrientation=(Orientation)((a+1)*c);
}



void AccelGyro::updateStatus(void) {
	updateOrientation();

}

Orientation AccelGyro::getSensorOrientation(void) {
	return(sensorOrientation);
}

} /* namespace PhysicalState_NS */