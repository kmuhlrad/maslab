#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <typeinfo>

#include "mraa.hpp"
#include "gyro.h"
#include "motor.h"
#include "piddrive.h"
#include "shield.h"

int running = 1;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  Shield *shield = new Shield();

  //two motor setup
  Motor left_motor(15, 0);
  Motor right_motor(4, 2);
  //Motor lift_motor(12, 3);

  Gyro gyro;

  PIDDrive drive(&left_motor, &right_motor, shield, 0.015, 0, 0.4);
  double start = gyro.get_angle();

  while (running) {
    drive.drive(start - 90, gyro.get_angle(), 0.);
    std::cout << gyro.get_angle() << std::endl;
  }
}
