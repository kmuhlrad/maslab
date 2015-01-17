#include "stacksearch.h"
//#include "mraa.hpp"

State::State(int num) {
	state_num = num;
}

int State::getState() {
	return state_num;
}