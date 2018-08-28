/*
 * FTBASerialMsgEverySec.h
 *
 *  Created on: 27 Aug 2018
 *      Author: yaniv
 */

#ifndef SRC_FTBASERIALMSGEVERYSEC_H_
#define SRC_FTBASERIALMSGEVERYSEC_H_

#include <FixedTimebasedAction.h>
#include "Log.h"

using namespace Log_NS;

namespace Behavior_ns {

class FTBA_SerialMsgEverySec: public FixedTimebasedAction
{
public:
	FTBA_SerialMsgEverySec(unsigned long delayInMillis, Log *LP);
	~FTBA_SerialMsgEverySec();

protected:
	void doYourThing(void);
	Log* L;
	String msg;
};

} /* namespace Behavior_ns */

#endif /* SRC_FTBASERIALMSGEVERYSEC_H_ */
