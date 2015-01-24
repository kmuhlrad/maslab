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
#include "ir.h"

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
  Motor left_motor(15, 2);
  Motor right_motor(4, 8);
  Motor lift_motor(12, 3);

  Gyro gyro;

  IR medA = IR(1, 6149.816568, 4.468768853);

  PIDDrive drive(&left_motor, &right_motor, shield, 0.015, 0, 0.4);

  while (running) {
    //drive.drive(0, gyro.get_angle(), 0.2);
    std::cout << "value: " << medA.read() << std::endl;
    std::cout << "distance: " << medA.getDistance() << std::endl;
  }
}
