#include "pwmpin.h"
#include "shield.h"
#include "mraa.hpp"

PWMPin::PWMPin(int pwm_pin) {
  pin = pwm_pin;
}

void PWMPin::write(Shield* shield, float value) {
  shield->writePWM(pin, value);
}