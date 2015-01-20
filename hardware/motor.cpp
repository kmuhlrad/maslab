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

//maybe hardcode cap for real thing?
void Motor::setSpeed(double speed) {
  //assert(-1.0 <= speed && speed <= 1.0);
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
  pwm.write(output);
}

//maybe hardcode cap for real thing?
void Motor::setSpeed(double speed, double cap) {
  //assert(-1.0 <= speed && speed <= 1.0);
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
  pwm.write(output);
}

void Motor::stop() {
  pwm.write(0.0);
  dir.write(0);
}