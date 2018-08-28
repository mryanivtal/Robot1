/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define TARGET_BOARD_NANO			//target board is Nano.  if not, comment this line


#include <Arduino.h>
#include "TimeBasedActionSet/FixedTimebasedAction.h"
#include "TimeBasedActionSet/TimeBasedActionSet.h"

#include "ActionClasses/FTBASerialWrite.h"

using namespace TimeBasedActionSet_NS;


//TODO: add pin defs per board according to precompiler params


//****************************************************Global variables

TimebasedAction* HappyBehavior[3];

FTBA_SerialWrite *MsgEverySec=0;
FTBA_SerialWrite *MsgEveryTwoSec=0;
FTBA_SerialWrite *MsgEveryFiveSec=0;

TimeBasedActionSet timelyBlink;

//****************************************************Setup
void setup()
{
	Serial.begin(115200);															//LOG
	while(!Serial);																	//LOG

	MsgEverySec=new FTBA_SerialWrite;
	MsgEveryTwoSec=new FTBA_SerialWrite;
	MsgEveryFiveSec=new FTBA_SerialWrite;

	MsgEverySec->setDelay(1000);
	MsgEverySec->setMsg("1Sec");
	MsgEveryTwoSec->setDelay(2000);
	MsgEveryTwoSec->setMsg("2 Sec");
	MsgEveryFiveSec->setDelay(5000);
	MsgEveryFiveSec->setMsg("5Sec");

	HappyBehavior[0]=MsgEverySec;
	HappyBehavior[1]=MsgEveryTwoSec;
	HappyBehavior[2]=MsgEveryFiveSec;

	timelyBlink.setBehavior(HappyBehavior, 3);

	Serial.println("Existing Setup() successfully");								//LOG
	delay(500);																		//LOG
}


//*****************************************************Loop
void loop()
{
	timelyBlink.run();

}
