#ifndef STACK_SEARCH_H
#define STACK_SEARCH_H

#include "state.h"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"
#include "../hardware/piddrive.h"

class StackSearch : public State {
	int getNext(SensorData data);
	void run(SensorData data);

	int count = 0;

	PIDDrive* drive;
	PIDDrive* driveA;
	PIDDrive* driveB;

	VideoCapture cap;

public:
	StackSearch(CubeSearch* cs, PIDDrive* dr, PIDDrive* a, PIDDrive* b);
	virtual int process(SensorData data);
	int getState(SensorData data);
};

#endif