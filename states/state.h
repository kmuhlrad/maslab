#ifndef STATE_H
#define STATE_H

class State {
protected:
	int state_num;

public:
	int getState();
	virtual int process()=0;
};

#endif