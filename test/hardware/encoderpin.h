#ifndef ENCODER_PIN_H
#define ENCODER_PIN_H

struct encoderpins {
public:
	mraa::Gpio* A;
	mraa::Gpio* B;
};

#endif