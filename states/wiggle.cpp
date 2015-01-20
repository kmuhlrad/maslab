#include "wiggle.h"
#include "robot_states.h"
//#include "mraa.hpp"

Wiggle::Wiggle() {
	state_num = WIGGLE;
}

int Wiggle::getState() {
	return state_num;
}

int Wiggle::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Wiggle::getNext(/*Data*/) {
	return LIFT;
	//return next_state; //IMPLEMENT THIS
}

void Wiggle::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}