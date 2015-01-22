#include <cassert>
#include <cmath>

#include "motor.h"
#include "shield.h"
#include "mraa.hpp"

Motor::Motor(int pwm_pin, int dir_pin) : dir(dir_pin) {
  pin = pwm_pin;  

  dir.dir(mraa::DIR_OUT);
  dir.write(0);
}

//maybe hardcode cap for real thing?
void Motor::setSpeed(Shield* shield, double speed, double cap) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  double output = fabs(speed);
  if (output > cap) {
    output = cap;
  }

  shield->writePWM(pin, output);
}

void Motor::setSpeed(Shield* shield, double speed) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  double output = fabs(speed);
  if (output > 0.3) {
    output = 0.3;
  }

  shield->writePWM(pin, output);
}

void Motor::stop(Shield* shield) {
  shield->writePWM(pin, 0.0);
  dir.write(0);
}