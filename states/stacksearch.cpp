#include "stacksearch.h"
//#include "mraa.hpp"

StackSearch::StackSearch(int num) : State(num) {

}

int StackSearch::getState() {
	return state_num;
}

int StackSearch::process() {
	return 1;
	//return next_state; //IMPLEMENT THIS
}

int StackSearch::getNext(/*Data*/) {
	return 1;
	//return next_state; //IMPLEMENT THIS
}

void StackSearch::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}