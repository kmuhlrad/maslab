#include <sys/time.h>

#include "stacksearch.h"
#include "robot_states.h"
#include "mraa.hpp"

#include "cubesearch.h"

StackSearch::StackSearch(CubeSearch cs) {
	state_num = STACKSEARCH;
}

int StackSearch::getState() {
	return state_num;
}

int StackSearch::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int StackSearch::getNext(/*Data*/) {
	return DRIVE;
	//return next_state; //IMPLEMENT THIS
	/*
	if (cs.findStack(cameraFeed) && cs.getTopColor() == data.rgswitch()) {
		return DRIVE;
	} else {
		return STACKSEARCH;
	}
	*/
}

void StackSearch::run(/*Data*/) {
	/*
	if (gyro.get_angle() > 360 || gyro.get_angle() < -360) {
		wallFollow() OR wallBounce();
	} else {
		drive.drive(gyro.get_angle() - 20, gyro.get_angle(), 0.2);
		usleep(200000);
	}
	*/
}