/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */


/**************************************************************************
 * 									Pins
 *************************************************************************/

#define DFPLAYER_PIN1 10			//DFPlayer Pins
#define DFPLAYER_PIN2 11

//Wire (AGBoard) pins are the I2C - D4, D5, cannot change
//voltage input 3.3~5V for both boards

/**************************************************************************
 * 									Includes
 *************************************************************************/

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

/***********************************************************************************************************
 * 									Global variables
 **********************************************************************************************************/


TimebasedAction* HappyBehavior[4]; 	//array of timing base-class pointers that will point to leaf classes (FTBA classes).
									//initialization of the FTBA classes will be done via proper leaf pointers,
									//running them will be done from base.

/**************************************************************************
 * 									TimebasedAction global variables
 *************************************************************************/


FTBA_PlayMP3Track *PlayFolder01EveryThreeSecs = 0;

TimeBasedActionSet robotBehavior;//the class that does the timing and running of the behavior (all action classes combined)

/**************************************************************************
 * 									DFPlayer global variables
 *************************************************************************/

SoftwareSerial DFSwSerial(DFPLAYER_PIN1, DFPLAYER_PIN2); // RX, TX for serial comms with DFPlayer
DFRobotDFPlayerMini DFPlayer;

unsigned long prevMillis = 0;			//for run millis measurement, LOG


/**************************************************************************
 * 									AccelGyro global variables
 *************************************************************************/

AccelGyro AGBoard;

/***********************************************************************************************************
 * 									void Setup()
 ***********************************************************************************************************/

void setup() {
	/**************************************************************************
	 * 									Init HW devices and connections
	 *************************************************************************/
	Serial.begin(115200);								//Init Serial
	delay(1000);

	//******************************

	Serial.println("Initializing DFSwSerial...)");
	DFSwSerial.begin(9600);								//Init Software serial for DFPlayer
	delay(1000);

	Serial.print("Initializing DFPlayer...");			//Init DFPlayer
	while (!DFPlayer.begin(DFSwSerial)) {
		Serial.print(".");
		delay(500);
	}
	Serial.println("Ready!");

	//******************************

	Serial.println("Initializing Wire...");				//Init wire (I2C connection) for AcceleratorGyro and future compass
	Wire.begin();
	delay(1000);

	Serial.println("Initializing AGBoard...");			//Init AccelGyro board
	AGBoard.begin();			//init AccelGyro board



	/**************************************************************************
	 * 									DFPlayer FTBA setup
	 *************************************************************************/

	PlayFolder01EveryThreeSecs = new FTBA_PlayMP3Track;

	PlayFolder01EveryThreeSecs->setDFPointer(&DFPlayer);//pointer to DF instance
	PlayFolder01EveryThreeSecs->setVolume(3);					//volume 10/30
	PlayFolder01EveryThreeSecs->setFolderAndTrackToPlay(1, 1, 4);//folder 01, song 001, 4 songs total
	PlayFolder01EveryThreeSecs->setPlayMode(1);		//iterate on entire folder
	PlayFolder01EveryThreeSecs->setDelay(4000);	//FTBA timing value in millis

	/**************************************************************************
	 * 				TimeBasedActionSet setup - combile all FTBAs to one behavior
	 *************************************************************************/

	HappyBehavior[0] = PlayFolder01EveryThreeSecs;
	robotBehavior.setBehavior(HappyBehavior, 1);//initializing the TimeBasedActionSet class to use that array


	/**************************************************************************
	 * 									Get out of Setup()
	 *************************************************************************/

	Serial.println("Existing Setup() successfully");					//LOG
	delay(500);															//LOG
}


/***********************************************************************************************************
 * 									void loop()
 ***********************************************************************************************************/

void loop() {

	robotBehavior.run();		// Now the TimeBasedActionSet executes actions in a timely manner
								// based on millis().
								// The plan is to use interrupts or other input method to update the behavior array per need
								// and then let this go on running on a different array(=different behavior).

								// TODO: the plan is to add RandomTimeBasedAction and some more action timing patterns
								// TODO: the plan is also to add many more action functions (e.g. play mp3, blink leds,
								// run led screens etc.) and use them with the timing classes,
								// The end game is an interactive doll with parallel behaviors based on light, direction, acceleration etc.

	AGBoard.sampleSensor();		//Sample AG board sensors
	AGBoard.updateAll();		//update all available AG conclusions based on samples



	/**************************************************************************
	 * 									Log to Serial
	 *************************************************************************/
	Serial.print(", getSensorOrientation()= ");
	Serial.print((int) AGBoard.getSensorOrientation());
	Serial.print(", atRest()= ");
	Serial.print((int) AGBoard.isAtRest());
	Serial.print(", deltaMillis()= ");
	Serial.print((long) (millis() - prevMillis));
	Serial.println();

	prevMillis = millis();
	//*************************************************************************

}
