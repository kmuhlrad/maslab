#ifndef DRIVE_H
#define DRIVE_H

#include "state.h"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"
#include "../hardware/piddrive.h"

class Drive : public State {
	int getNext(SensorData data);
	void run(SensorData data);

	PIDDrive* drive;
	CubeSearch* cubesearch;

	VideoCapture* cap;

	double curAng;

public:
	Drive(CubeSearch* cs, VideoCapture* vid, PIDDrive* dr);
	virtual int process(SensorData data);
	int getState();
};

#endif