#ifndef START_H
#define START_H

#include "state.h"

class Start : public State {
	void run(/*Data*/);
public:
	Start();
	virtual int process(/*Data*/);
	int getState();
};

#endif