#include "start.h"
#include "robot_states.h"
//#include "mraa.hpp"

Start::Start() {
	state_num = START;
}

int Start::getState() {
	return state_num;
}

int Start::process() {
	//run();
	return STACKSEARCH;
	
	/*
	if (startSwitch) {
		return STACKSEARCH;
	} else {
		return START;
	}
	*/
}

void Start::run(/*Data*/) {
	//initialize stuff
}