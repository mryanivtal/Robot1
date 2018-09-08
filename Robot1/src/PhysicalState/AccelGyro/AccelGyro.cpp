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

	for (i = 0; i < 3; i++) {
		gyroRawData[i] += GYRO_CALIBRATION[i];			// Calibrate gyro data
		accelRawData[i] += ACCL_CALIBRATION[i];			// Calibrate accelerometer data
	}

//  //***************************LOG*********************************************
//	for(i=0; i<3; i++) {												//LOG
//		Serial.print(accelRawData[i]);									//LOG
//		Serial.print(",");												//LOG
//	}																	//LOG
//	for(i=0; i<3; i++) {												//LOG
//		Serial.print(gyroRawData[i]);									//LOG
//		Serial.print(",");												//LOG
//	}																	//LOG
//	Serial.println();													//LOG
//	//***************************LOG*********************************************

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

//	  //***************************LOG*********************************************
//	  for(i=0; i<3; i++) {														//LOG
//		  Serial.print(mvaOrientationAccel[i]);									//LOG
//		  Serial.print(",");													//LOG
//	  }																			//LOG
//	  Serial.print(sensorOrientation);											//LOG
//	  Serial.println();														//LOG
//	  //***************************LOG*********************************************

}

void PhysicalState_NS::AccelGyro::updateAtRest(void) {
	  int i;
	  long previousVals[6];
	  bool stillAtRest=1;


	  for(i=0; i<3; i++) {								//Moving average for atRest estimation - accelerometer
		  previousVals[i]=mvaAtRest[i];					//store previous value for comparison
		  mvaAtRest[i] = (mvaAtRest[i]*(MVA_FOR_AT_REST-1) + accelRawData[i]) / MVA_FOR_AT_REST;

		  if(abs(mvaAtRest[i]-previousVals[i]) > DIFF_TRESHOLD_FOR_AT_REST) 		//is the diff outside reasonable white noise levels?
			  stillAtRest=0;
	  }

	  for(i=0; i<3; i++) {								//Moving average for atRest estimation - Gyro
		  previousVals[i+3]=mvaAtRest[i+3];					//store previous value for comparison
		  mvaAtRest[i+3] = (mvaAtRest[i+3]*(MVA_FOR_AT_REST-1) + gyroRawData[i]) / MVA_FOR_AT_REST;

		  if(abs(mvaAtRest[i+3]-previousVals[i+3]) > DIFF_TRESHOLD_FOR_AT_REST) 		//is the diff outside reasonable white noise levels?
			  stillAtRest=0;
	  }

	  if(stillAtRest==0) {
		  atRest=0;
		  atRestCycles=0;
	  }
	  else {
		  atRestCycles+=1;
		  if(atRestCycles >= CYCLES_FOR_AT_REST)
			  atRest=1;
	  }

//	  //***************************LOG*********************************************
//	  for(i=0; i<6; i++) {														//LOG
//		  Serial.print(mvaAtRest[i]);											//LOG
//		  Serial.print(",");													//LOG
//	  }																			//LOG
//	  Serial.print(stillAtRest);												//LOG
//	  Serial.println("");														//LOG
//	  //***************************LOG*********************************************


}

bool AccelGyro::isAtRest(void) {
	return(atRest);
}


void AccelGyro::updateAll(void) {
	updateOrientation();
	updateAtRest();

}

Orientation AccelGyro::getSensorOrientation(void) {
	return(sensorOrientation);
}


} /* namespace PhysicalState_NS */
