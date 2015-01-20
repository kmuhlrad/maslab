#include "drive.h"
#include "robot_states.h"
//#include "mraa.hpp"

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
	return WIGGLE;
	//return next_state; //IMPLEMENT THIS
}

void Drive::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}