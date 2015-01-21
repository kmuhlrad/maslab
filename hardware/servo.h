#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"
#include "shield.h"

class Servo {
	Shield shield;
	int pin;
public:
	Servo(int pwm_pin);
	void setDegree(double deg);
	void write(float value);
};

#endif