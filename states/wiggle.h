#ifndef WIGGLE_H
#define WIGGLE_H

#include "state.h"

class Wiggle : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Wiggle();
	virtual int process(/*Data*/);
	int getState();
};

#endif