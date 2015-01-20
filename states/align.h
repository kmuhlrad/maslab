#ifndef ALIGN_H
#define ALIGN_H

#include "state.h"

class Align : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Align();
	virtual int process(/*Data*/);
	int getState();
};

#endif