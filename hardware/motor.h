#ifndef MOTOR_H
#define MOTOR_H

#include "mraa.hpp"
#include "shield.h"

class Motor {
	//pins
	mraa::Gpio dir;
	int pin;
public:
	//constructor
	Motor(int pwm_pin, int dir_pin);

	//methods
	void setSpeed(Shield* shield, double speed, double cap);
	void setSpeed(Shield* shield, double speed);
	void stop(Shield* shield);
};

#endif