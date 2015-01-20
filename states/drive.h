#ifndef DRIVE_H
#define DRIVE_H

#include "state.h"

class Drive : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Drive();
	virtual int process(/*Data*/);
	int getState();
};

#endif