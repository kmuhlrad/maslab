#ifndef SERVO_H
#define SERVO_H

#include "mraa.hpp"

class Servo {
	mraa::Pwm pin;
public:
	Servo(int pin_num);
	void setDegree(int deg); //maybe change to double?
	void stop(); //need this?
};

#endif