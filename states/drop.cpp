#include <iostream>

#include "drop.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "../hardware/liftmech.h"
#include "sensordata.h"

Drop::Drop(LiftMech* lm) {
	state_num = DROP;
	liftmech = lm;
}

int Drop::getState() {
	return state_num;
}

int Drop::process(SensorData data) {
	run();
}

int Drop::getNext() {
	//return DROP;
}

void Drop::run() {
    std::cout << "scoring" << std::endl;
	liftmech->score();
	/*
	STOP EVERYTHING
	*/
}
