/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

/* Connection schema for NodeMCU:
 * GY521 	- 	Arduino:
 * VCC 		-	3.3V
 * GND		-	GND
 * SCL		-	D6
 * SDA		-	D7
 *
 * DFPlayer -	Arduino
 * VCC		-	5V
 * RX		-	D11
 * TX		-	D10
 * DAC_R	-
 * DAC_I	-
 * SPK1		-
 * GND		-	GND
 * SPK2		-
 */



/**************************************************************************
 * 									Pins
 *************************************************************************/

#define DFPLAYER_PIN1 5			//DFPlayer Pins
#define DFPLAYER_PIN2 4

#define OLED_RESET 0

//Wire (AGBoard) pins are the I2C - D4, D5, cannot change
//voltage input 3.3~5V for both boards

/**************************************************************************
 * 									Includes
 *************************************************************************/

#include <Arduino.h>
#include <Wire.h>

#include "TimeBasedActionSet/TimingClasses/TimeBasedActionSet.h"
#include "TimeBasedActionSet/TimeBasedActions/FTBASerialWrite.h"

#include <SoftwareSerial.h>
#include "DFRobotPlayer/DFRobotDFPlayerMini.h"
#include "TimeBasedActionSet/TimeBasedActions/FTBAPlayMP3Track.h"

#include "AccelGyro/AccelGyro.h"
#include <RobotMood.h>

using namespace TimeBasedActionSet_NS;
using namespace PhysicalState_NS;
using namespace RobotMood_NS;

/***********************************************************************************************************
 * 									Global variables
 **********************************************************************************************************/

RobotMood robotMood;
Mood currentMood;

TimebasedAction* HappyBehavior[4]; 	//array of timing base-class pointers that will point to leaf classes (FTBA classes).
									//initialization of the FTBA classes will be done via proper leaf pointers,
									//running them will be done from base.
TimebasedAction* UpsideDownBehavior[4];
TimebasedAction* ExcitedBehavior[4];
TimebasedAction* BoredBehavior[4];


/**************************************************************************
 * 									TimebasedAction global variables
 *************************************************************************/


FTBA_PlayMP3Track *PlayFolder01Periodically = 0;		//"Happy behavior" MP3s
FTBA_PlayMP3Track *PlayFolder02Periodically = 0;		//"Upside down behavior" MP3s
FTBA_PlayMP3Track *PlayFolder03Periodically = 0;		//"Bored behavior" MP3s
FTBA_PlayMP3Track *PlayFolder04Periodically = 0;		//"Excited behavior" MP3s

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

	//Happy
	PlayFolder01Periodically = new FTBA_PlayMP3Track;
	PlayFolder01Periodically->setDFPointer(&DFPlayer);//pointer to DF instance
	PlayFolder01Periodically->setVolume(3);					//volume 10/30
	PlayFolder01Periodically->setFolderAndTrackToPlay(1, 1, 3);//folder 01, song 001, 3 songs total
	PlayFolder01Periodically->setPlayMode(1);		//iterate on entire folder
	PlayFolder01Periodically->setDelay(9000);	//FTBA timing value in millis

	//Upside down
	PlayFolder02Periodically = new FTBA_PlayMP3Track;
	PlayFolder02Periodically->setDFPointer(&DFPlayer);//pointer to DF instance
	PlayFolder02Periodically->setVolume(3);					//volume 10/30
	PlayFolder02Periodically->setFolderAndTrackToPlay(2, 1, 2);//folder 01, song 001, 2 songs total
	PlayFolder02Periodically->setPlayMode(1);		//iterate on entire folder
	PlayFolder02Periodically->setDelay(5000);	//FTBA timing value in millis

	//Bored
	PlayFolder03Periodically = new FTBA_PlayMP3Track;
	PlayFolder03Periodically->setDFPointer(&DFPlayer);//pointer to DF instance
	PlayFolder03Periodically->setVolume(3);					//volume 10/30
	PlayFolder03Periodically->setFolderAndTrackToPlay(3, 1, 2);//folder 01, song 001, 2 songs total
	PlayFolder03Periodically->setPlayMode(1);		//iterate on entire folder
	PlayFolder03Periodically->setDelay(10000);	//FTBA timing value in millis

	//Excited
	PlayFolder04Periodically = new FTBA_PlayMP3Track;
	PlayFolder04Periodically->setDFPointer(&DFPlayer);//pointer to DF instance
	PlayFolder04Periodically->setVolume(3);					//volume 10/30
	PlayFolder04Periodically->setFolderAndTrackToPlay(4, 1, 1);//folder 01, song 001, 2 songs total
	PlayFolder04Periodically->setPlayMode(1);		//iterate on entire folder
	PlayFolder04Periodically->setDelay(4000);	//FTBA timing value in millis

	/**************************************************************************
	 * 				TimeBasedActionSet setup - combile all FTBAs to one behavior
	 *************************************************************************/

	HappyBehavior[0] = PlayFolder01Periodically;
	UpsideDownBehavior[0] = PlayFolder02Periodically;
	BoredBehavior[0] = PlayFolder03Periodically;
	ExcitedBehavior[0] = PlayFolder04Periodically;

	robotBehavior.setBehavior(HappyBehavior, 1);//initializing the TimeBasedActionSet class to use that array

	currentMood=robotMood.getMood();		//get current mood for LOG
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



	AGBoard.sampleSensor();		//Sample AG board sensors
	AGBoard.updateAll();		//update all available AG conclusions based on samples

	robotMood.update(AGBoard.getSensorOrientation(), AGBoard.isAtRest(), AGBoard.getTotalLinearForce()); //update robot mood
	if(robotMood.getMoodChanged()) { 			//Was mood changed right now?
		currentMood=robotMood.getMood();		//get current mood

		switch (currentMood) {
			case Happy:
				robotBehavior.setBehavior(HappyBehavior, 1);
				break;
			case Excited:
				robotBehavior.setBehavior(ExcitedBehavior, 1);
				break;
			case Bored:
				robotBehavior.setBehavior(BoredBehavior, 1);
				break;
			case UpsideDown:
				robotBehavior.setBehavior(UpsideDownBehavior, 1);
				break;
		}
	}

	robotBehavior.run();		// Now the TimeBasedActionSet executes actions in a timely manner
								// based on millis().
								// The plan is to use interrupts or other input method to update the behavior array per need
								// and then let this go on running on a different array(=different behavior).

								// TODO: the plan is to add RandomTimeBasedAction and some more action timing patterns
								// TODO: the plan is also to add many more action functions (e.g. play mp3, blink leds,
								// run led screens etc.) and use them with the timing classes,
								// The end game is an interactive doll with parallel behaviors based on light, direction, acceleration etc.



	/**************************************************************************
	 * 									Log to Serial - sensor board status
	 *************************************************************************/
	Serial.print("getSensorOrientation()= ");
	Serial.print((int) AGBoard.getSensorOrientation());
	Serial.print(", atRest()= ");
	Serial.print((int) AGBoard.isAtRest());
	Serial.print(", getTotalLinearForce()= ");
	Serial.print(AGBoard.getTotalLinearForce());
	Serial.print(", deltaMillis()= ");
	Serial.print((long) (millis() - prevMillis));
	Serial.print(", currentMood = ");
	Serial.print((int) currentMood);
	Serial.println();

	prevMillis = millis();
	//*************************************************************************

}
