#include <sys/time.h>
#include <iostream>

#include "drive.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"
#include "../hardware/piddrive.h"

Drive::Drive(CubeSearch* cs, VideoCapture* vid, PIDDrive* dr) {
	state_num = DRIVE;

	drive = dr;
	cubesearch = cs;

	cap = vid;
	double curAngle = 0;
}

int Drive::getState() {
	return state_num;
}

int Drive::process(SensorData data) {
	std::cout << "Drive: process before" << std::endl;
	int next = getNext(data);
	std::cout << "Drive: process after" << std::endl;
	if (next != state_num) {
		return next;
	} else {
		curAng = data.getGyroAngle();
		run(data);
		return state_num;
	}
}

int Drive::getNext(SensorData data) {
	std::cout << "Drive: getNext" << std::endl;
	if(data.getDistanceB() < 8) {
		//cap.release();
		return LIFT;
	} else {
		return DRIVE;
	}

	/* IMPLEMENT SOON
	 else if (!foundStack || wrongColor) { ////FINISH///////
		return STACKSEARCH;
	*/
}

void Drive::run(SensorData data) {
	std::cout << "Drive: process first" << std::endl;
	Mat img;
	cap >> img; //maybe request 6 images
	std::cout << "Drive: process second" << std::endl;
	cubesearch->processImage(img);
	std::cout << "Drive: process third" << std::endl;
	if (cubesearch->findStack(img)) {
		std::cout << "Drive: driving towards stack" << std::endl;
		drive->drive(curAng + cubesearch->getAngle(img)[0], data.getGyroAngle(), 0.25);
		sleep(.5);
	} else {
		std::cout << "Drive: driving straight" << std::endl;
	    drive->drive(data.getGyroAngle(), data.getGyroAngle(), 0.3);
	    usleep(200000);
	}
}