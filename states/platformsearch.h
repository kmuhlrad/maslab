#ifndef PLATFORMSEARCH_H
#define PLATFORMSEARCH_H

#include "state.h"

class PlatformSearch : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	PlatformSearch();
	virtual int process(/*Data*/);
	int getState();
};

#endif