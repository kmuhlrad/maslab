// Compile with:
// g++ motor.cpp -o motor -lmraa
// Controls a motor through a range of speeds using the Cytron motor controller
// Pwm on pin 9, and dir on pin 8.

#include <cassert>
#include <cmath>
#include <csignal>
#include <iostream>

#include "gyro.h"
#include "mraa.hpp"

int running = 1;
double integral = 0;

struct timeval start;
struct timeval end;

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

//PID coefficients
//NEED TO BE TESTED
int P = 0.001;
int I = 0.001;
int D = -0.001;

void drive_straight(mraa::Pwm& left_motor, mraa::Gpio& left_dir,
                    mraa::Pwm& right_motor, mraa::Gpio& right_dir,
                    Gyro gyro,
                    double desired, double estimated, double speed) {
  assert(-1.0 <= desired && desired <= 1.0);
  
  //set direction
  //CHECK DIRECTIONS AND THAT THIS WORKS
  if (speed < 0) {
    left_dir.write(1);
    right_dir.write(0);
  }
  else {
    left_dir.write(0);
    right_dir.write(1);
  }

  gettimeofday(&end, NULL);

  int diffSec = end.tv_sec - start.tv_sec;
  int diffUSec = end.tv_usec - start.tv_usec;
  double dT = (double)diffSec + 0.000001*diffUSec;

  double diff = desired - estimated;
  double intetral += diff*dT;
  double derivative = gyro.get_angular_velocity(); //THIS DOESN'T EXIST YET
  double power = P*diff + I*integral + D*derivative;

  left_motor.write(speed + power);
  right_motor.write(speed - power);

  gettimeofday(&start, NULL);
}

void turn() {
  //copy code from turning maybe???
}

void stop(mraa::Pwm& pwm, mraa::Gpio& dir) {
  pwm.write(0);
  dir.write(0);
}

void sig_handler(int signo) {
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

  Gyro gyro;

  gettimeofday(&start, NULL);
  
  while (running) {
    //NEED TO CHECK DESIRED AND ESTIMATED BASED ON GYRO OUTPUT
    //desired should come from external input: cube location or something
    //estimated should come from the current gryo angle reading
    //speed should depend on external input from distance sensors or camera

    //need to update within the function? Or will this be good enough?
    drive_straight(left_motor, left_dir, right_motor, right_dir, gyro, 0.5, gyro.get_angle(), 0.5);
  }

  ~Gyro();
}