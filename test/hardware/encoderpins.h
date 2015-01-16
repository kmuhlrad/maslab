#ifndef ENCODER_PIN_H
#define ENCODER_PIN_H

struct encoderpins {
public:
	encoderpins(int a_pin, int b_pin);
	mraa::Gpio* A;
	mraa::Gpio* B;
};

#endif