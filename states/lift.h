#ifndef LIFT_H
#define LIFT_H

#include "state.h"
#include "mraa.hpp"
#include "../hardware/liftmech.h"

class Lift : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);

	LiftMech* liftmech;

	int counter;
public:
	Lift(LiftMech* lm);
	virtual int process(/*Data*/);
	int getState();
};

#endif