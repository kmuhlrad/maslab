#ifndef ENCODER_H
#define ENCODER_H

#include "mraa.hpp"
#include "encoderpins.h"

class Encoder {
	//total number of encoder counts
 	int counts;
 	
public:
	Encoder(int a_pin, int b_pin);
	int getCounts();
	void resetCounts();
	void encoderA_handler();
 	void encoderB_handler();

 	//need to be pointers?
 	mraa::Gpio A;
 	mraa::Gpio B;
};

#endif