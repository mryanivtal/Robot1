/*
 * RobotMood.h
 *
 *  Created on: Sep 28, 2018
 *      Author: yaniv
 */

#ifndef SRC_ROBOTMOOD_H_
#define SRC_ROBOTMOOD_H_

#include <Arduino.h>
#include <AccelGyro.h>
#include <RobotMood.h>

#define MIN_TIME_IN_MOOD 2000			//Minimum time (millis) to stay in certain mood
#define LINEAR_FORCE_TO_GET_EXCITED 3	//Min linear force to get to excited mood
#define UPSIDE_DOWN_ORIENTATION ZNeg	//sensor orientation when doll is upside down
#define TIME_TO_GET_BORED 15000			//tIME (MILLIS) TILL THE DOLL GETS BORED


using namespace PhysicalState_NS;

namespace RobotMood_NS {

typedef enum Mood {
	Happy=1,
	UpsideDown=2,
	Bored=3,
	Excited=4
} Mood;


class RobotMood {
public:
	RobotMood();
	virtual ~RobotMood();

	Mood getMood(void);
	bool getMoodChanged(void);
	void update(Orientation orientation, bool atRest, unsigned float totalLinearForce);

protected:
	Mood mood=Happy;							//Current mood

	Mood prevMood=Happy;						//previous mood, before last change
	bool moodChanged=0;
	unsigned long moodTimeChanged=0;

	Orientation prevOrientation=ZPos;			//previous orientation (For reference to identify changes)
	bool orientationChanged=0;
	unsigned long orientationTimeChanged=0;

	bool atRest=1;
	bool atRestChanged=0;
	unsigned long atRestTimeChanged=0;


	unsigned float prevTotalLinearForce=0;
	bool totalLinearForceTrend=0;				//1 if increasing, 0 if decreasing


};

} /* namespace RobotMood_NS */

#endif /* SRC_ROBOTMOOD_H_ */
