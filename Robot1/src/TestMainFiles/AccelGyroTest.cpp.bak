

#include <Arduino.h>
#include <Wire.h>

#include "TimeBasedActionSet/TimingClasses/TimeBasedActionSet.h"
#include "TimeBasedActionSet/TimeBasedActions/FTBASerialWrite.h"

#include "SoftwareSerial.h"
#include "DFRobotPlayer/DFRobotDFPlayerMini.h"
#include "TimeBasedActionSet/TimeBasedActions/FTBAPlayMP3Track.h"

#include "PhysicalState/AccelGyro/AccelGyro.h"

using namespace TimeBasedActionSet_NS;
using namespace PhysicalState_NS;

//***************************************************** Vars

AccelGyro AGBoard;
unsigned long prevMillis=0;

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	delay(1000);

	AGBoard.begin();

	Serial.println("Existing Setup() successfully");								//LOG
	delay(500);
}

void loop()
{
	AGBoard.sampleSensor();
	AGBoard.updateAll();

//
//	Serial.print(", getSensorOrientation()= ");					//LOG
//	Serial.print((int)AGBoard.getSensorOrientation());			//LOG
//	Serial.print(", atRest()= ");								//LOG
//	Serial.print((int)AGBoard.isAtRest());						//LOG
//	Serial.print(", deltaMillis()= ");							//LOG
//	Serial.print((long)(millis()-prevMillis));					//LOG
//	Serial.println();											//LOG
//
//	prevMillis=millis();										//LOG



}
