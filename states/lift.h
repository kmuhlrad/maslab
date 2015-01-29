#ifndef LIFT_H
#define LIFT_H

#include "state.h"
#include "mraa.hpp"
#include "../hardware/liftmech.h"
#include "sensordata.h"

class Lift : public State {
	int getNext();
	void run();

	LiftMech* liftmech;

	int counter;
public:
	Lift(LiftMech* lm);
	virtual int process(SensorData data);
	int getState();
};

#endif