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

String a="1sec";
String b="2sec";
String c="5sec";


FTBA_SerialMsgEverySec MsgEverySec(1000);
FTBA_SerialMsgEverySec MsgEveryTwoSec(2000);
FTBA_SerialMsgEverySec MsgEveryFiveSec(5000);

Behavior timelyBlink(HappyBehavior[0], 3);


//****************************************************Setup
void setup()
{
	Serial.begin(115200);
	while(!Serial);
	HappyBehavior[0]=&MsgEverySec;
	HappyBehavior[1]=&MsgEveryTwoSec;
	HappyBehavior[2]=&MsgEveryFiveSec;

	Serial.println("Existing Setup() successfully");			//LOG
	delay(1000);												//LOG

}


//*****************************************************Loop
void loop()
{
	timelyBlink.run();

}
