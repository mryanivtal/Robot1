

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

	Serial.print(", getSensorOrientation()= ");
	Serial.print((int)AGBoard.getSensorOrientation());
	Serial.print(", atRest()= ");
	Serial.println((int)AGBoard.isAtRest());

	delay(30);


}
