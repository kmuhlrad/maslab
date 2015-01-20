#ifndef DROP_H
#define DROP_H

#include "state.h"

class Drop : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	Drop();
	virtual int process(/*Data*/);
	int getState();
};

#endif