#ifndef PWM_PIN_H
#define PWM_PIN_H

#include "mraa.hpp"
#include "shield.h"

class PWMPin {
	int pin;
public:
	PWMPin(int pwm_pin);
	void write(Shield* shield, float value);
};

#endif