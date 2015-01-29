#include <sys/time.h>

#include "platformsearch.h"
#include "robot_states.h"
#include "sensordata.h"
//#include "mraa.hpp"

PlatformSearch::PlatformSearch() {
	state_num = PLATFORMSEARCH;
	//reset gyro angle;
}

int PlatformSearch::getState() {
	return state_num;
}

int PlatformSearch::process(SensorData data) {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int PlatformSearch::getNext(/*Data*/) {
	return ALIGN;
	/*
	if (found && closeEnough) {
		return ALIGN;
	} else {
		return PLATFORMSEARCH;
	}
	*/
}

void PlatformSearch::run(/*Data*/) {
	/*
	if (gyro.get_angle() > 360 || gyro.get_angle() < -360) {
		wallFollow() OR wallBounce();
	} else {
		drive.drive(gyro.get_angle() - 20, gyro.get_angle(), 0.2);
	}
	*/
}