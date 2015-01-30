#ifndef ALIGN_H
#define ALIGN_H

#include "state.h"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/platfinder.h"
#include "../hardware/piddrive.h"

class Align : public State {
	int getNext(SensorData data);
	void run(SensorData data);

	PIDDrive* drive;
	PlatformFinder* platfinder;

	VideoCapture* cap;

	double curAng;
public:
	Align(PlatformFinder* pf, VideoCapture* vid, PIDDrive* dr);
	virtual int process(SensorData data);
	int getState();
};

#endif