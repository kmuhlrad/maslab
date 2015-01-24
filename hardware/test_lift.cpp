#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <typeinfo>

#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"
#include "servo.h"
#include "liftmech.h"

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
  Motor left_motor = new Motor(15, 2);
  Motor right_motor = new Motor(4, 8);
  Motor lift_motor = new Motor(12, 3);

  Servo left_lift = new Servo(9);
  Servo right_lift = new Servo(8);

  Servo left_door = new Servo(1);
  Servo right_door = new Servo(0);

  LiftMech lift(&left_motor, &right_motor, &lift_motor,
                &left_door, &right_door, &left_lift, &right_lift,
                4, 5);
  /*mraa::Gpio bottombeam = mraa::Gpio(5);
  bottombeam.dir(mraa::DIR_IN);

  mraa::Gpio topbeam = mraa::Gpio(4);
  topbeam.dir(mraa::DIR_IN);*/

  int up = 1;
  int test = 0;
  while (running && !test) {
    lift.collect(shield);
    test = 1;
    std::cout << "collected" << std::endl;
    //lift.reset();
  }
}
