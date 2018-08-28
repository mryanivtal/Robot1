/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define TARGET_BOARD_NANO			//target board is Nano.  if not, comment this line


#include <Arduino.h>
#include "FTBASerialMsg.h"
#include "Behavior.h"

using namespace Behavior_ns;


//TODO: add pin defs per board according to precompiler params


//****************************************************Global variables

TimebasedAction* HappyBehavior[3];

FTBA_SerialMsg *MsgEverySec=0;
FTBA_SerialMsg *MsgEveryTwoSec=0;
FTBA_SerialMsg *MsgEveryFiveSec=0;

Behavior timelyBlink;


//****************************************************Setup
void setup()
{
	Serial.begin(115200);															//LOG
	while(!Serial);																	//LOG

	MsgEverySec=new FTBA_SerialMsg;
	MsgEveryTwoSec=new FTBA_SerialMsg;
	MsgEveryFiveSec=new FTBA_SerialMsg;

	MsgEverySec->init(1000, "1 Sec");
	MsgEveryTwoSec->init(2000, "2 Sec");
	MsgEveryFiveSec->init(5000, "5 Sec");

	Serial.println("EtimelyBlink.setBehavior(HappyBehavior[0], 3) done");			//LOG

	HappyBehavior[0]=MsgEverySec;
	HappyBehavior[1]=MsgEveryTwoSec;
	HappyBehavior[2]=MsgEveryFiveSec;

	timelyBlink.setBehavior(HappyBehavior, 3);

	Serial.println("Existing Setup() successfully");								//LOG
	delay(1000);																	//LOG

}


//*****************************************************Loop
void loop()
{
	timelyBlink.run();

}
