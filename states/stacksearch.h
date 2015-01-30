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
	void wallFollowCW(SensorData data);
	void wallFollowCCW(SensorData data);

	int count;

	CubeSearch* cubesearch;
	PIDDrive* drive;
	PIDDrive* driveA;
	PIDDrive* driveB;
	PIDDrive* driveC;

	VideoCapture* cap;

public:
	StackSearch(CubeSearch* cs, VideoCapture* vid, PIDDrive* dr, PIDDrive* a, PIDDrive* b, PIDDrive* c);
	virtual int process(SensorData data);
	int getState();
};

#endif
