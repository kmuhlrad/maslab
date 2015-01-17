#include "collect.h"
//#include "mraa.hpp"

Collect::Collect(int num) : State(num) {

}

/*int Collect::getState() {
	return state_num;
}*/

int Collect::process() {
	return 0;
	//return next_state; //IMPLEMENT THIS
}

int Collect::getNext(/*Data*/) {
	return 0;
	//return next_state; //IMPLEMENT THIS
}

void Collect::run(/*Data*/) {
	//DO STUFF
	//printf("run\n");
}