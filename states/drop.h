#ifndef DROP_H
#define DROP_H

#include "state.h"

#include "mraa.hpp"
#include "../hardware/liftmech.h"

class Drop : public State {
	int getNext();
	void run();

	LiftMech* liftmech;
public:
	Drop(LiftMech* lm);
	virtual int process();
	int getState();
};

#endif