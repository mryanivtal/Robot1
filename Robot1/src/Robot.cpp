/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define TARGET_BOARD_NANO			//target board is Nano.  if not, comment this line


#include <Arduino.h>
#include "FTBASerialMsgEverySec.h"
#include "TimebasedAction.h"
#include "Behavior.h"

using namespace Behavior_ns;


//TODO: add pin defs per board according to precompiler params


//****************************************************Global variables

TimebasedAction* HappyBehavior[3];

FTBA_SerialMsgEverySec *MsgEverySec=0;
FTBA_SerialMsgEverySec *MsgEveryTwoSec=0;
FTBA_SerialMsgEverySec *MsgEveryFiveSec=0;

Behavior timelyBlink;


//****************************************************Setup
void setup()
{
	Serial.begin(115200);
	while(!Serial);

	MsgEverySec=new FTBA_SerialMsgEverySec;
	MsgEveryTwoSec=new FTBA_SerialMsgEverySec;
	MsgEveryFiveSec=new FTBA_SerialMsgEverySec;

	MsgEverySec->init(1000, "1Sec");
	MsgEveryTwoSec->init(2000, "2Sec");
	MsgEveryFiveSec->init(5000, "1Sec");

	timelyBlink.setBehavior(HappyBehavior[0], 3);
	Serial.println("EtimelyBlink.setBehavior(HappyBehavior[0], 3) done");			//LOG

	HappyBehavior[0]=MsgEverySec;
	HappyBehavior[1]=MsgEveryTwoSec;
	HappyBehavior[2]=MsgEveryFiveSec;

	Serial.println("Existing Setup() successfully");			//LOG
	delay(1000);												//LOG

}


//*****************************************************Loop
void loop()
{
	timelyBlink.run();

}
