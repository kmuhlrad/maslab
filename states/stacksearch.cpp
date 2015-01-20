#include "stacksearch.h"
#include "robot_states.h"
//#include "mraa.hpp"

StackSearch::StackSearch() {
	state_num = STACKSEARCH;
}

int StackSearch::getState() {
	return state_num;
}

int StackSearch::process() {
	return STACKSEARCH;
	//return next_state; //IMPLEMENT THIS
}

int StackSearch::getNext(/*Data*/) {
	return STACKSEARCH;
	//return next_state; //IMPLEMENT THIS
}

void StackSearch::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}