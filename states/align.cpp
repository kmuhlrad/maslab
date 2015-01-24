#include "align.h"
#include "robot_states.h"
//#include "mraa.hpp"

Align::Align() {
	state_num = ALIGN;
}

int Align::getState() {
	return state_num;
}

int Align::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Align::getNext(/*Data*/) {
	return DROP;
	/*
	if (aligned) {
		return DROP;
	} else if (lostPlatform) {
		return PLATFORMSEARCH;
	} else {
		return ALIGN;
	}
	*/
}

void Align::run(/*Data*/) {
	/*
	if (canSeePlatform) {
		drive.drive(platform_angle, gyro.get_angle(), 0.25);
		sleep(.5);
	} else {
	    drive.drive(gyro.get_angle, gyro.get_angle(), 0.3);
	    usleep(200000);
	}
	*/
}