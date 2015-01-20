#include "collect.h"
#include "robot_states.h"
//#include "mraa.hpp"

Collect::Collect() {
	state_num = DRIVE;
}

int Collect::getState() {
	return state_num;
}

int Collect::process() {
	return START;
	//return next_state; //IMPLEMENT THIS
}

int Collect::getNext(/*Data*/) {
	return START;
	//return next_state; //IMPLEMENT THIS
}

void Collect::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}