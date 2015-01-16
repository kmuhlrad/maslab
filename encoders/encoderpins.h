#ifndef ENCODER_PIN_H
#define ENCODER_PIN_H

#include "mraa.hpp"

class Encoderpins {
public:
	Encoderpins(int a_pin, int b_pin);
	mraa::Gpio* A;
	mraa::Gpio* B;
};

#endif