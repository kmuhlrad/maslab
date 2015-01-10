#include <cassert>
#include <cmath>
#include <csignal>
#include <iostream>
#include <sys/time.h>

#include "mraa.hpp"


int running = 1;

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

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

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  // short-range IR pin
  mraa::Gpio sensor = mraa::Gpio(12);
  sensor.dir(mraa::DIR_IN);

  // Motor pins
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
  
  while (running) {
    // 20us trigger pulse (must be at least 10us)

    if (!sensor.read()) {
      setMotorSpeed(left_motor, left_dir, 0.0);
      setMotorSpeed(right_motor, right_dir, 0.0);
    }
    else {
      setMotorSpeed(left_motor, left_dir, -0.4);
      setMotorSpeed(right_motor, right_dir, 0.4);
    }

    // Must pause at least 60ms between measurements
    usleep(200000.0);
  }
}

