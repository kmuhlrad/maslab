#ifndef LIFT_H
#define LIFT_H

#include "state.h"

class Lift : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Lift();
	virtual int process(/*Data*/);
	int getState();
};

#endif