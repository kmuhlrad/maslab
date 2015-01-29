#ifndef START_H
#define START_H

#include "state.h"
#include "sensordata.h"

class Start : public State {
	void run(/*Data*/);
public:
	Start();
	virtual int process(SensorData data);
	int getState();
};

#endif