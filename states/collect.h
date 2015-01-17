#ifndef COLLECT_H
#define COLLECT_H

#include "state.h"

class Collect : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Collect(int num);
	virtual int process(/*Data*/);
	int getState();
};

#endif