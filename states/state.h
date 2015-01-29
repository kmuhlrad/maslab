#ifndef STATE_H
#define STATE_H

#include "sensordata.h"

class State {
protected:
	int state_num;

public:
	int getState();
	virtual int process(SensorData data)=0;
};

#endif