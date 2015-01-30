#ifndef DRIVE_H
#define DRIVE_H

#include "state.h"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"
#include "../hardware/piddrive.h"
#include "../hardware/servo.h"

class Drive : public State {
	int getNext(SensorData data);
	void run(SensorData data);

	PIDDrive* drive;
	CubeSearch* cubesearch;

    Servo* left_door;
    Servo* right_door;

	VideoCapture* cap;

	double curAng;

public:
	Drive(CubeSearch* cs, VideoCapture* vid, PIDDrive* dr, Servo* left, Servo* right);
	virtual int process(SensorData data);
	int getState();
};

#endif
