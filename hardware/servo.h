#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"
#include "shield.h"

class Servo {
	int pin;
public:
	Servo(int pwm_pin, Shield *shield);
	void setDegree(double deg);
	void write(float value);
};

#endif