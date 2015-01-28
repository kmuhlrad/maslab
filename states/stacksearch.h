#ifndef STACK_SEARCH_H
#define STACK_SEARCH_H

#include "state.h"
#include "cubesearch.h"

class StackSearch : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	StackSearch(CubeSearch cs);
	virtual int process(/*Data*/);
	int getState();
};

#endif