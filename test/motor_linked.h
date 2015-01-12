#ifndef MOTOR_H
#define MOTOR_H

//I don't know if I need this...
//#include "mraa.hpp"

class Motor {
public:
	void setMotorSpeed(mraa::Pwm& pwm, mraa::Gpio& dir, double speed);
	void stop(mraa::Pwm& pwm, mraa::Gpio& dir);
};

#endif