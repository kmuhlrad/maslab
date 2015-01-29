#include <sys/time.h>
#include <iostream>

#include "drive.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"
#include "../hardware/piddrive.h"

Drive::Drive(CubeSearch* cs, PIDDrive* dr) {
	state_num = DRIVE;

	drive = dr;
	cubesearch = cs;

	cap = VideoCapture(0);
}

int Drive::getState() {
	return state_num;
}

int Drive::process(SensorData data) {
	int next = getNext(data);
	if (next != state_num) {
		return next;
	} else {
		run(data);
		return state_num;
	}
}

int Drive::getNext(SensorData data) {
	if(data.getDistanceB() < 8) {
		return LIFT;
	} else {
		return DRIVE;
	}

	/* EVENTUALLY IMPLEMENT IF NEEDED
	 else if (!foundStack || wrongColor) { ////FINISH///////
		return STACKSEARCH;
	*/
}

void Drive::run(SensorData data) {
	Mat img;
	cap >> img; //maybe request 6 images
	cubesearch->processImage(img);
	if (cubesearch->findStack(img)) {
		std::cout << "Drive: driving towards stack" << std::endl;
		drive->drive(cubesearch->getAngle(img), data.getGyroAngle(), 0.25);
		sleep(.5);
	} else {
		std::cout << "Drive: driving straight" << std::endl;
	    drive->drive(data.getGyroAngle(), data.getGyroAngle(), 0.3);
	    usleep(200000);
	}
}