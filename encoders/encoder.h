#ifndef ENCODER_H
#define ENCODER_H

#include "mraa.hpp"
#include "encoderpins.h"

class Encoder {
	//need to be pointers?
	/*mraa::Gpio A;
 	mraa::Gpio B;*/

 	//total number of encoder counts
 	int counts;

 	void encoderA_handler(void* args);
 	void encoderB_handler(void* args);
public:
	Encoder(Encoderpins* ep);
	int getCounts(); //need params? Start, end, time, what?
	void resetCounts();
	int getPosition(); //????
};

#endif