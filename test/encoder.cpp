// Compile with:
// g++ encoder.cpp -o encoder -lmraa

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

  //encoder input pins
  mraa::Gpio A = mraa::Gpio(12);
  mraa::Gpio B = mraa::Gpio(2);

  double speed = -1.0;
  while (running) {
    //std::cout << "Speed: " << "0.5" << std::endl;
    setMotorSpeed(right_motor, right_dir, -0.5);
    setMotorSpeed(left_motor, left_dir, 0.5);
    std::cout << "Encoder A: " << A.read() << std::endl;
    std::cout << "Encoder B: " << B.read() << std::endl;

    usleep(100000);
    /*speed += 0.1;
    if (speed > 1.0) {
      speed = -1.0;
      // Let the motor spin down
      setMotorSpeed(right_motor, right_dir, 0.0);
      sleep(2.0);
    }*/
  }
}