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

#include "TimeBasedActionSet/TimingClasses/TimeBasedActionSet.h"
#include "TimeBasedActionSet/TimeBasedActions/FTBASerialWrite.h"

#include "SoftwareSerial.h"
#include "DFRobotPlayer/DFRobotDFPlayerMini.h"

using namespace TimeBasedActionSet_NS;


//TODO: add pin defs per board according to precompiler params


//*******************************TimebasedAction variables

TimebasedAction* HappyBehavior[3];			//array of timing base-class pointers that will point to leaf classes (FTBA classes).
											//initialization of the FTBA classes will be done via proper leaf pointers,
											//running them will be done from base.

FTBA_SerialWrite *MsgEverySec=0;			//Three FTBA class pointers
FTBA_SerialWrite *MsgEveryTwoSec=0;
FTBA_SerialWrite *MsgEveryFiveSec=0;

TimeBasedActionSet timelyBlink;				//the class that does the timing of all action classes combined

//*******************************DFPlayer variables

SoftwareSerial mySoftwareSerial(DFPLAYER_PIN1,DFPLAYER_PIN2); // RX, TX for serial comms with DFPlayer
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


//**************************************************************
//****************************************************Setup*****

void setup()
{
	Serial.begin(115200);
	delay(1000);
	//*******************************Setup TimebasedAction stuff***

	MsgEverySec=new FTBA_SerialWrite;		//initializing FTBA (Leaf) classes, these have both function and timing
	MsgEveryTwoSec=new FTBA_SerialWrite;
	MsgEveryFiveSec=new FTBA_SerialWrite;

	MsgEverySec->setDelay(1000);			//initialize timing value
	MsgEverySec->setMsg("1Sec");			//initializing action value
	MsgEveryTwoSec->setDelay(2000);
	MsgEveryTwoSec->setMsg("2 Sec");
	MsgEveryFiveSec->setDelay(5000);
	MsgEveryFiveSec->setMsg("5Sec");

	HappyBehavior[0]=MsgEverySec;			//populating the actionset array pointers with all actions in set
	HappyBehavior[1]=MsgEveryTwoSec;
	HappyBehavior[2]=MsgEveryFiveSec;

	timelyBlink.setBehavior(HappyBehavior, 3);	//initializing the TimeBasedActionSet class to use that array


	//***************************************Setup DFPlayer stuff***

	mySoftwareSerial.begin(9600);
	delay(1000);

	Serial.print("Initializing DFPlayer, may take 3~5 seconds)");
	while(!myDFPlayer.begin(mySoftwareSerial))
	{
		Serial.print(".");
	    delay(500);
	}
	Serial.println("Ready!");

	myDFPlayer.volume(10);  //Set volume value. From 0 to 30
	myDFPlayer.play(1);  //Play the first mp3

	//*********************************************************

	Serial.println("Existing Setup() successfully");								//LOG
	delay(500);																		//LOG
}


//**************************************************************
//*****************************************************Loop*****
void loop()
{
	timelyBlink.run();			// Now the TimeBasedActionSet executes actions in a timely manner
								// based on millis().
								// The plan is to use interrupts or other input method to update the behavior array per need
								// and then let this go on running on a different array(=different behavior).

								// TODO: the plan is to add RandomTimeBasedAction and some more action timing patterns
								// TODO: the plan is also to add many more action functions (e.g. play mp3, blink leds,
								// run led screens etc.) and use them with the timing classes,
								// The end game is an interactive doll with parallel behaviors based on light, direction, acceleration etc.


}
