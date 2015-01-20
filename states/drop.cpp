#include "drop.h"
#include "robot_states.h"
//#include "mraa.hpp"

Drop::Drop() {
	state_num = DROP;
}

int Drop::getState() {
	return state_num;
}

int Drop::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Drop::getNext(/*Data*/) {
	return STACKSEARCH;
	//return next_state; //IMPLEMENT THIS
}

void Drop::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}