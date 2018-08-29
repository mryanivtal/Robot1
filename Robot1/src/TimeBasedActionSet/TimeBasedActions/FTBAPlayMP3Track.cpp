/*
 * FTBAPlaySound.cpp
 *
 *  Created on: Aug 29, 2018
 *      Author: yaniv
 */

#include "FTBAPlayMP3Track.h"

namespace TimeBasedActionSet_NS {

FTBA_PlayMP3Track::FTBA_PlayMP3Track() {
}

FTBA_PlayMP3Track::~FTBA_PlayMP3Track() {
}

void FTBA_PlayMP3Track::setDFPointer(DFRobotDFPlayerMini* myDFP) {
	myDF=myDFP;
}

void FTBA_PlayMP3Track::setFolderAndTrackToPlay(byte folderNoP,byte trackNoP, byte tracksInFolderP) {
	folderNo=folderNoP;
	nextTrackNo=trackNoP;
	tracksInFolder=tracksInFolderP;
//	tracksInFolder=myDF->readFileCountsInFolder(folderNo);

//	Serial.println("FTBA_PlayMP3Track::setFolderAndTrackToPlay:");		//LOG
//	Serial.print("folderNo=");											//LOG
//	Serial.print(folderNo);												//LOG
//	Serial.print(", nextTrackNo=");										//LOG
//	Serial.print(nextTrackNo);											//LOG
//	Serial.print(", tracksInFolder=");									//LOG
//	Serial.println(tracksInFolder);										//LOG

}

void FTBA_PlayMP3Track::setPlayMode(byte playModeP) {		//0-same track every time, 1-iterate on entire folder
	playMode=playModeP;
}

void FTBA_PlayMP3Track::play(void) {
//	Serial.println("FTBA_PlayMP3Track::play:");		//LOG
//	Serial.print("folderNo=");											//LOG
//	Serial.print(folderNo);												//LOG
//	Serial.print(", nextTrackNo=");										//LOG
//	Serial.print(nextTrackNo);											//LOG
//	Serial.print(", tracksInFolder=");									//LOG
//	Serial.println(tracksInFolder);										//LOG

	myDF->playFolder(folderNo, nextTrackNo);  //play specific mp3, e.g. SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
	updateNextSong();
}

void FTBA_PlayMP3Track::setVolume(byte volumeP) {
	myDF->volume(volumeP);  //Set volume value. From 0 to 30

}

void FTBA_PlayMP3Track::updateNextSong(void) {
	if(playMode==1) {
		nextTrackNo++;
		if(nextTrackNo > tracksInFolder) nextTrackNo=1;
	}

//	Serial.println("FTBA_PlayMP3Track::updateNextSong - after function done");		//LOG
//	Serial.print("folderNo=");											//LOG
//	Serial.print(folderNo);												//LOG
//	Serial.print(", nextTrackNo=");										//LOG
//	Serial.print(nextTrackNo);											//LOG
//	Serial.print(", tracksInFolder=");									//LOG
//	Serial.println(tracksInFolder);										//LOG
}

void FTBA_PlayMP3Track::doYourThing(void) {
	play();

}

} /* namespace TimeBasedActionSet_NS */
