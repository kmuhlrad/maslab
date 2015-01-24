#include <iostream>

#include "lift.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "../hardware/liftmech.h"

Lift::Lift(LiftMech* lm) {
	state_num = LIFT;
	liftmech = lm;

	counter = 0;
}

int Lift::getState() {
	return state_num;
}

int Lift::process() {
	if (getNext() != state_num) {
		return getNext();
	} else {
		run();
		return state_num;
	}
}

int Lift::getNext(/*Data*/) {
	//return PLATFORMSEARCH;
    if (counter == 0) {
    	counter = 1;
    	return LIFT;
    } else {
    	return PLATFORMSEARCH;
    }
    
	//return next_state; //IMPLEMENT THIS
}

void Lift::run(/*Data*/) {
    std::cout << "collecting" << std::endl;
	liftmech.reset();
	liftmech.collect();
}