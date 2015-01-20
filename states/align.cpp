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
	//return next_state; //IMPLEMENT THIS
}

void Align::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}