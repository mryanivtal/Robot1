/*
 * FTBASerialWrite.h
 *
 *  Created on: Aug 28, 2018
 *      Author: yaniv
 */

#ifndef SRC_ACTIONCLASSES_FTBASERIALWRITE_H_
#define SRC_ACTIONCLASSES_FTBASERIALWRITE_H_

#include "SerialWrite.h"
#include "../TimeBasedActionSet/FixedTimebasedAction.h"

namespace TimeBasedActionSet_NS {

class FTBA_SerialWrite: public FixedTimebasedAction, public SerialWrite
{
public:
	FTBA_SerialWrite();
	virtual ~FTBA_SerialWrite();

	void doYourThing(void);
};

} /* namespace TimeBasedActionSet_NS */

#endif /* SRC_ACTIONCLASSES_FTBASERIALWRITE_H_ */
