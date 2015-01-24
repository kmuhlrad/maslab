#include <iostream>

#include "drop.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "../hardware/liftmech.h"

Drop::Drop(LiftMech* lm) {
	state_num = DROP;
	liftmech = lm;
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
	return DROP;
}

void Drop::run(/*Data*/) {
    std::cout << "scoring" << std::endl;
	liftmech->score();
	/*
	STOP EVERYTHING
	*/
}
