#ifndef PLATFORMSEARCH_H
#define PLATFORMSEARCH_H

#include "state.h"
#include "sensordata.h"

class PlatformSearch : public State {
	int getNext(/*Data*/);
	void run(/*Data*/);
public:
	PlatformSearch();
	virtual int process(SensorData data);
	int getState();
};

#endif