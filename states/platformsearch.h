#ifndef PLATFORMSEARCH_H
#define PLATFORMSEARCH_H

#include "state.h"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/platfinder.h"
#include "../hardware/piddrive.h"

class PlatformSearch : public State {
	int getNext(SensorData data);
	void run(SensorData data);
	void wallFollow(SensorData data);

	PlatformFinder* platfinder;
	PIDDrive* drive;
	PIDDrive* driveA;
	PIDDrive* driveB;

	VideoCapture* cap;

public:
	PlatformSearch(PlatformFinder* pf, VideoCapture* vid, PIDDrive* dr, PIDDrive* a, PIDDrive* b);
	virtual int process(SensorData data);
	int getState();
};

#endif