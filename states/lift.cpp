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
   if (counter == 4) {
    	return PLATFORMSEARCH;
    } else {
        counter++;
    	return LIFT;
    }
    
    /*
    if (noStacksLeft || time < 1 min) {
		return PLATFORMSEARCH;
    } else if (successful) {
		return STACKSEARCH;
    } else {
		return LIFT;
    }
    */
}

void Lift::run(/*Data*/) {
	liftmech->reset();
	liftmech->collect();
}
