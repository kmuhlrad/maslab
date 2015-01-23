//stop ALL the motors!

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

int running = 1; //SET BACK TO 1 FOR AUTO

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  Motor left(15, 2);
  Motor right(0, 8);
  Motor lift(12, 3);

  Shield *shield = new Shield();

  while (running) {
    left.stop(shield);
    right.stop(shield);
    lift.stop(shield);
    usleep(100000);
  }
}
