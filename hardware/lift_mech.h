#ifndef LIFT_MECH_H
#define LIFT_MECH_H

#include "mraa.hpp"

class LiftMech {
	//total number of encoder counts
 	int counts;
 	
public:
	LiftMech(int a_pin, int b_pin);
	int getCounts();
	void resetCounts();
	void encoderA_handler();
 	void encoderB_handler();

 	//need to be pointers?
 	mraa::Gpio A;
 	mraa::Gpio B;
};

#endif