#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"
#include "shield.h"

class Servo {
	int pin;
public:
	Servo(int pwm_pin);
	void setDegree(Shield *shield, double deg);
	void write(Shield *shield, float value);
};

#endif