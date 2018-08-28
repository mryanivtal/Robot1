/*
 * FTBASerialMsgEverySec.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_FTBASERIALMSG_H_
#define SRC_FTBASERIALMSG_H_
#include <Arduino.h>
#include <FixedTimebasedAction.h>

namespace Behavior_ns {

class FTBA_SerialMsg: public FixedTimebasedAction
{
public:
	FTBA_SerialMsg();
	~FTBA_SerialMsg();
	void init(unsigned long delayInMillisP, String msgP);

protected:
	void doYourThing(void);
	String msg;
};

} /* namespace Behavior_ns */

#endif /* SRC_FTBASERIALMSG_H_ */
