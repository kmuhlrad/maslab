#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"

class Servo {
	mraa::Pwm pwm;
public:
	Servo(int pwm_pin);
	void setDegree(int deg); //maybe change to double?
	void stop(); //need this?
};

#endif