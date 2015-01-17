#ifndef STACK_SEARCH_H
#define STACK_SEARCH_H

#include "state.h"

class StackSearch : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	StackSearch(int num);
	virtual int process(/*Data*/);
	int getState();
};

#endif