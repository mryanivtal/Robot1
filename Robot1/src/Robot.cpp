/*
 * Robot.cpp
 *
 *  Created on: Aug 27, 2018
 *      Author: yaniv
 */

#define TARGET_BOARD_NANO			//target board is Nano.  if not, comment this line

#include <Arduino.h>
#include <Log.h>

using namespace Log_NS;


//TODO: add pin defs per board according to precompiler params


void setup()
{
	Log SerialLog;			//begin serial communication via USB for logging
	SerialLog.println("Testing log mechanism!");

}

void loop()
{

}
