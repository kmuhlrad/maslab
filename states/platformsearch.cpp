#include "platformsearch.h"
#include "robot_states.h"
//#include "mraa.hpp"

PlatformSearch::PlatformSearch() {
	state_num = PLATFORMSEARCH;
}

int PlatformSearch::getState() {
	return state_num;
}

int PlatformSearch::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int PlatformSearch::getNext(/*Data*/) {
	return ALIGN;
	//return next_state; //IMPLEMENT THIS
}

void PlatformSearch::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}