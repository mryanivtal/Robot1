/*
 * RobotMood.cpp
 *
 *  Created on: Sep 28, 2018
 *      Author: yaniv
 */

#include <RobotMood.h>

namespace RobotMood_NS {

RobotMood::RobotMood() {
	// TODO Auto-generated constructor stub

}

RobotMood::~RobotMood() {
	// TODO Auto-generated destructor stub
}

Mood RobotMood::getMood(void) {
	return(mood);
}

bool RobotMood::getMoodChanged(void) {
	return(moodChanged);
}

void RobotMood::update(Orientation orientationP, bool atRestP, unsigned float totalLinearForceP) {

	if(prevOrientation != orientationP) {					//update orientation params
		orientationChanged=1;
		orientationTimeChanged=millis();
	}

	if (atRestP != atRest) {								//update at rest params
		atRestChanged=1;
		atRestTimeChanged=millis();
	}
														//update total linear force params
	if(prevTotalLinearForce >= totalLinearForceP) {			//Linear force decreasing?
		totalLinearForceTrend=0;
	}
	else {													//increasing?
		totalLinearForceTrend=1;
	}


	//Now check if need to update mood!
	moodChanged=0;		//default - mood not changed

	if(millis()-moodTimeChanged >= MIN_TIME_IN_MOOD) {		//update mood only if required time passed since lst change

		if(totalLinearForceP >= LINEAR_FORCE_TO_GET_EXCITED) {	//Force big enough to get excited?
			if(mood != Excited) {								//Not excited Yet?
				prevMood=mood;									//Get excited!
				mood=Excited;
				moodChanged=1;
				moodTimeChanged=millis();
			}
		}
		else if(orientationP == UPSIDE_DOWN_ORIENTATION) {		//Doll is upside down?
			if(mood != UpsideDown) {							//mood not there yet?
				prevMood=mood;									//Get excited!
				mood=UpsideDown;
				moodChanged=1;
				moodTimeChanged=millis();
			}
		}
		else if ( (atRestP==1)	&&  	(millis()-atRestTimeChanged >= TIME_TO_GET_BORED))	//doll not moving for a long time?
			if(mood != Bored) {								//not bored yet?
				prevMood=mood;									//Get excited!
				mood=Bored;
				moodChanged=1;
				moodTimeChanged=millis();
		}

		else if (mood != Happy) {
			prevMood=mood;									//Get excited!
			mood=Happy;
			moodChanged=1;
			moodTimeChanged=millis();
		}
	}

	atRest=atRestP;
	prevTotalLinearForce=totalLinearForceP;
	prevOrientation = orientationP;
}

} /* namespace Mood_NS */
