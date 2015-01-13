// Compile with:
// g++ motor.cpp -o motor -lmraa
// Controls a motor through a range of speeds using the Cytron motor controller
// Pwm on pin 9, and dir on pin 8.

//new added comment

#include <cassert>
#include <cmath>

#include "motor.h"
#include "mraa.hpp"

Motor::Motor(int pwm_pin, int dir_pin) : pwm(pwm_pin), dir(dir_pin) {
  //pwm = mraa::Pwm(pwm_pin);
  pwm.write(0.0);
  pwm.enable(true);

  //dir = mraa::Gpio(dir_pin);
  dir.dir(mraa::DIR_OUT);
  dir.write(0);
}

void Motor::setSpeed(double speed) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  pwm.write(fabs(speed));
}

void Motor::stop() {
  pwm.write(0.0);
  dir.write(0);
}