#include <iostream>

#include "lift.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "../hardware/liftmech.h"
#include "sensordata.h"

Lift::Lift(LiftMech* lm) {
	state_num = LIFT;
	liftmech = lm;

	counter = 0;
}

int Lift::getState() {
	return state_num;
}

int Lift::process(SensorData data) {
	run();
	return getNext();
}

int Lift::getNext() {
	return PLATFORMSEARCH; 
   /*if (counter == 4) {
    	return PLATFORMSEARCH;
    } else {
        return STACKSEARCH;
    }*/
    
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

void Lift::run() {
	counter++;
	liftmech->reset();
	liftmech->collect();
}
