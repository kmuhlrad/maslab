// Compile with:
// g++ motor.cpp -o motor -lmraa
// Controls a motor through a range of speeds using the Cytron motor controller
// Pwm on pin 9, and dir on pin 8.

//new added comment

#include <cassert>
#include <cmath>
#include <csignal>
#include <iostream>

#include "mraa.hpp"

int running = 1;

void setMotorSpeed(mraa::Pwm& pwm, mraa::Gpio& dir, double speed) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  pwm.write(fabs(speed));
}

void stop(mraa::Pwm& pwm, mraa::Gpio& dir) {
  pwm.write(0);
  dir.write(0);
}

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);
  
  //two motor setup
  mraa::Pwm left_motor = mraa::Pwm(9);
  left_motor.write(0.0);
  left_motor.enable(true);
  mraa::Gpio left_dir = mraa::Gpio(8);
  left_dir.dir(mraa::DIR_OUT);
  left_dir.write(0);

  mraa::Pwm right_motor = mraa::Pwm(5);
  right_motor.write(0.0);
  right_motor.enable(true);
  mraa::Gpio right_dir = mraa::Gpio(4);
  right_dir.dir(mraa::DIR_OUT);
  right_dir.write(0);

  //testing code
  while(running) {
    setMotorSpeed(left_motor, left_dir, 0.2);
    setMotorSpeed(right_motor, right_dir, -0.2);
  }
}

