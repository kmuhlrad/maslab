#ifndef ENCODER_H
#define ENCODER_H

#include "mraa.hpp"

class Encoder {
	//need to be pointers?
	/*mraa::Gpio A;
 	mraa::Gpio B;*/

 	struct encoder;
 	//total number of encoder counts
 	int counts;

 	void encoderA_handler(void* args);
 	void encoderB_handler(void* args);
public:
	Encoder(int a_pin, int b_pin);
	~Encoder();
	int getCounts(); //need params? Start, end, time, what?
	void resetCounts();
	int getPosition(); //????
};

#endif