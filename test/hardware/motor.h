#ifndef MOTOR_H
#define MOTOR_H

#include "mraa.hpp"

class Motor {
	//pins
	mraa::Pwm pwm;
	mraa::Gpio dir;
public:
	//constructor
	Motor(int pwm_pin, int dir_pin);

	//methods
	void setSpeed(double speed);
	void stop();
};

#endif