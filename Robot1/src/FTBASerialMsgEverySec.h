/*
 * FTBASerialMsgEverySec.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_FTBASERIALMSGEVERYSEC_H_
#define SRC_FTBASERIALMSGEVERYSEC_H_

#include <FixedTimebasedAction.h>

namespace Behavior_ns {

class FTBA_SerialMsgEverySec: public FixedTimebasedAction
{
public:
	FTBA_SerialMsgEverySec();
	~FTBA_SerialMsgEverySec();
	void init(unsigned long delayInMillisP, String msgP);

protected:
	void doYourThing(void);
	String msg;
};

} /* namespace Behavior_ns */

#endif /* SRC_FTBASERIALMSGEVERYSEC_H_ */
