/*
 * FTBAPlaySound.h
 *
 *  Created on: Aug 29, 2018
 *      Author: yaniv
 */

#ifndef SRC_DFROBOTPLAYER_FTBAPLAYSOUND_H_
#define SRC_DFROBOTPLAYER_FTBAPLAYSOUND_H_

#include "../../DFRobotPlayer/DFRobotDFPlayerMini.h"
#include "../TimingClasses/FixedTimebasedAction.h"

namespace TimeBasedActionSet_NS {

class FTBA_PlayMP3Track: public DFRobotDFPlayerMini, public FixedTimebasedAction {
public:
	FTBA_PlayMP3Track();
	virtual ~FTBA_PlayMP3Track();
	
	void doYourThing(void);

	void setDFPointer(DFRobotDFPlayerMini* myDFP);		//assign DFPlayer class instance to this class
	void setFolderAndTrackToPlay(byte folderNoP, byte trackNoP, byte tracksInFolderP);	//On init - select SD folder and track no. to play (1-99)
	void setPlayMode(byte playModeP);				//0-same track every time, 1-iterate on entire folder
	void setVolume(byte volume);					//volume - 0-30

	void play(void);							//Play next song from specific folder

protected:
	DFRobotDFPlayerMini* myDF=0;
	int folderNo=1;
	byte nextTrackNo=1;
	byte playMode=0;
	byte tracksInFolder=0;

	void updateNextSong(void);
};

} /* namespace TimeBasedActionSet_NS */

#endif /* SRC_DFROBOTPLAYER_FTBAPLAYSOUND_H_ */
