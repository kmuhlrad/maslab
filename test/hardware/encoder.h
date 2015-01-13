#ifndef ENCODER_H
#define ENCODER_H

#include "mraa.hpp"

class Encoder {
	mraa::Gpio A;
 	mraa::Gpio B;
public:
	Encoder(int a_pin, int b_pin);
	int getCounts(); //need params? Start, end, time, what?
	int getPosition(); //????
};

#endif