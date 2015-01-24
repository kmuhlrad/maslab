#include "drive.h"
#include "robot_states.h"

#include "mraa.hpp"

Drive::Drive() {
	state_num = DRIVE;
}

int Drive::getState() {
	return state_num;
}

int Drive::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Drive::getNext(/*Data*/) {
	return LIFT;
	/*
	if(reachedStack) {
		return LIFT;
	} else if (!foundStack || wrongColor) {
		return STACKSEARCH;
	} else {
		return DRIVE;
	}
	*/
}

void Drive::run(/*Data*/) {
	/*
	if (canSeeStack) {
		drive.drive(stack_angle, gyro.get_angle(), 0.25);
		sleep(.5);
	} else {
	    drive.drive(gyro.get_angle, gyro.get_angle(), 0.3);
	    usleep(200000);
	}
	*/
}