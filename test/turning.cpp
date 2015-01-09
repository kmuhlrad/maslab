// Compile with:
// g++ turning.cpp -o turning -lmraa
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

//these two functions just explicitly set the motor forward or backward
//they are redundant and might not be useful
//take them out if not needed
void forward(mraa::Pwm& pwm, mraa::Gpio& dir, double speed) {
  assert(speed >= 0.0 && speed <= 1.0);
  dir.write(0);
  pwm.write(speed);
}

void reverse(mraa::Pwm& pwm, mraa::Gpio& dir, double speed) {
  assert(speed >= 0.0 && speed <= 1.0);
  dir.write(1);
  pwm.write(speed);
}

void stop(mraa::Pwm& pwm, mraa::Gpio& dir) {
  pwm.write(0);
  dir.write(0);
}

void turn(mraa::Pwm& m1, mraa::Gpio& dir1, 
                mraa::Pwm& m2, mraa::Gpio& dir2,
                double speed, double us) {
  
  setMotorSpeed(m1, dir1, speed);
  setMotorSpeed(m2, dir2, speed);
  usleep(us);
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

  double speed = -1.0;
  while (running) {
    //std::cout << "Speed: " << "0.5" << std::endl
    //drive forward to the cubes
    setMotorSpeed(right_motor, right_dir, -0.3);
    setMotorSpeed(left_motor, left_dir, 0.3);
    sleep(1.0);

    //slow down and stop
    stop(right_motor, right_dir);
    stop(left_motor, left_dir);
    sleep(1.0);

    //+ for right
    //- for left
    //maybe???

    //turn right
    turn(right_motor, right_dir, left_motor, left_dir, 0.2, 500000);

    //slow down
    turn(right_motor, right_dir, left_motor, left_dir, 0.0, 500000);

    //turn left
    turn(right_motor, right_dir, left_motor, left_dir, -0.2, 500000);

    //slow down
    turn(right_motor, right_dir, left_motor, left_dir, 0.0, 500000);

    //turn right
    turn(right_motor, right_dir, left_motor, left_dir, 0.2, 500000);

    //slow down
    turn(right_motor, right_dir, left_motor, left_dir, 0.0, 500000);

    //turn left
    turn(right_motor, right_dir, left_motor, left_dir, -0.2, 500000);

    //slow down
    turn(right_motor, right_dir, left_motor, left_dir, 0.0, 500000);


    /*speed += 0.1;
    if (speed > 1.0) {
      speed = -1.0;
      // Let the motor spin down
      setMotorSpeed(right_motor, right_dir, 0.0);
      sleep(2.0);
    }*/
  }
}