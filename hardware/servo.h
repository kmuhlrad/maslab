#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"

class Servo {
	mraa::Pwm pwm;
public:
	Servo(int pwm_pin);
	void setDegree(double deg);
	void write(float value);
	void stop(); //need this?
};

#endif