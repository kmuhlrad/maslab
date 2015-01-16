#ifndef ENCODER_PIN_H
#define ENCODER_PIN_H

struct encoderpin {
public:
	mraa::Gpio* A;
	mraa::Gpio* B;
};

#endif