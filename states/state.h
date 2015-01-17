#ifndef STATE_H
#define STATE_H

class State {
protected:
	int state_num;

public:
	State(int num);
	int getState();
	virtual int process()=0;
};

#endif