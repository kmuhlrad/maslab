#include "lift.h"
#include "robot_states.h"
//#include "mraa.hpp"

Lift::Lift() {
	state_num = LIFT;
}

int Lift::getState() {
	return state_num;
}

int Lift::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Lift::getNext(/*Data*/) {
	return PLATFORMSEARCH;
	//return next_state; //IMPLEMENT THIS
}

void Lift::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}