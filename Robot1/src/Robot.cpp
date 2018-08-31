/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define TARGET_BOARD_NANO			//target board is Nano.  if not, comment this line

#define DFPLAYER_PIN1 10
#define DFPLAYER_PIN2 11

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


//TODO: add pin defs per board according to precompiler params


//**************************************************** Global Variables ********************************************
//******************************************************************************************************************

TimebasedAction* HappyBehavior[4];			//array of timing base-class pointers that will point to leaf classes (FTBA classes).
											//initialization of the FTBA classes will be done via proper leaf pointers,
											//running them will be done from base.

//*******************************TimebasedAction variables

FTBA_SerialWrite *MsgEverySec=0;			//Four FTBA class pointers
FTBA_SerialWrite *MsgEveryTwoSec=0;
FTBA_SerialWrite *MsgEveryFiveSec=0;
FTBA_PlayMP3Track *PlayFolder01EveryThreeSecs=0;


TimeBasedActionSet robotBehavior;			//the class that does the timing and running of the behavior (all action classes combined)

//*******************************DFPlayer variables

SoftwareSerial DFSwSerial(DFPLAYER_PIN1,DFPLAYER_PIN2); // RX, TX for serial comms with DFPlayer
DFRobotDFPlayerMini DFPlayer;


//**************************************************** Setup ******************************************************
//*****************************************************************************************************************

void setup()
{
	Serial.begin(115200);
	Wire.begin();
	delay(1000);
	//******************************* Setup FTBA_SerialWrite objects ***

	MsgEverySec=new FTBA_SerialWrite;		//initializing FTBA (Leaf) classes, these have both function and timing
	MsgEveryTwoSec=new FTBA_SerialWrite;
	MsgEveryFiveSec=new FTBA_SerialWrite;

	MsgEverySec->setDelay(1000);			//initialize timing value
	MsgEverySec->setMsg("1Sec");			//initializing action value
	MsgEveryTwoSec->setDelay(2000);
	MsgEveryTwoSec->setMsg("2 Sec");
	MsgEveryFiveSec->setDelay(5000);
	MsgEveryFiveSec->setMsg("5Sec");


	//*************************************** Setup DFPlayer objects ***

	DFSwSerial.begin(9600);
	delay(1000);

	Serial.print("Initializing DFPlayer, may take 3~5 seconds)");
	while(!DFPlayer.begin(DFSwSerial))
	{
		Serial.print(".");
	    delay(500);
	}
	Serial.println("Ready!");

	PlayFolder01EveryThreeSecs=new FTBA_PlayMP3Track;

	PlayFolder01EveryThreeSecs->setDFPointer(&DFPlayer);				//pointer to DF instance
	PlayFolder01EveryThreeSecs->setVolume(3);							//volume 10/30
	PlayFolder01EveryThreeSecs->setFolderAndTrackToPlay(1,1,7);			//folder 01, song 001, 4 songs total
	PlayFolder01EveryThreeSecs->setPlayMode(1);							//iterate on entire folder
	PlayFolder01EveryThreeSecs->setDelay(4000);							//FTBA timing value in millis

	//***************************************Now combine all FTBAs to one whole behavior


	HappyBehavior[0]=MsgEverySec;			//populating the actionset array pointers with all actions in set
	HappyBehavior[1]=MsgEveryTwoSec;		//Order is not important, they will be executed based on timing
	HappyBehavior[2]=MsgEveryFiveSec;
	HappyBehavior[3]=PlayFolder01EveryThreeSecs;

	robotBehavior.setBehavior(HappyBehavior, 4);	//initializing the TimeBasedActionSet class to use that array

	//********************************************************* Get out

	Serial.println("Existing Setup() successfully");								//LOG
	delay(500);																		//LOG
}


//**************************************************** Loop *******************************************************
//*****************************************************************************************************************


void loop()
{
	robotBehavior.run();			// Now the TimeBasedActionSet executes actions in a timely manner
								// based on millis().
								// The plan is to use interrupts or other input method to update the behavior array per need
								// and then let this go on running on a different array(=different behavior).

								// TODO: the plan is to add RandomTimeBasedAction and some more action timing patterns
								// TODO: the plan is also to add many more action functions (e.g. play mp3, blink leds,
								// run led screens etc.) and use them with the timing classes,
								// The end game is an interactive doll with parallel behaviors based on light, direction, acceleration etc.


}