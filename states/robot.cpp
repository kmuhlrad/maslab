//main robot file
//compile with:
//g++ gyro.cpp motor.cpp robot.cpp -o robot -lmraa
//[ADD IN OTHER FILES LATER AS NEEDED]

//PINS:
//1
//2 - Short range IR
//3 -
//4 - Right wheel dir
//5 - Right wheel pwm
//6
//7 - DON'T USE!!!!
//8 - Left wheel dir
//9 - Left wheel pwm
//10 - Gyro CS
//11 - Gyro MOSI
//12 - Gyro MISO
//13 - Gyro SCLK

//A0 -
//A1 - Med range IR A
//A2 -
//A3 -
//A4 -
//A5 -

#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <unistd.h>

/*#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"
#include "servo.h"*/

#include "robot_states.h"
#include "state.h"

#include "start.h"
#include "stacksearch.h"
#include "drive.h"
#include "wiggle.h"
#include "lift.h"
#include "platformsearch.h"
#include "align.h"
#include "drop.h"



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

  Start *start = new Start();
  StackSearch *stack = new StackSearch();
  Drive *drive = new Drive();
  Wiggle *wiggle = new Wiggle();
  Lift *lift = new Lift();
  PlatformSearch *platform = new PlatformSearch();
  Align *align = new Align();
  Drop *drop = new Drop();

  State *states[8] = {start, stack, drive, wiggle, lift, platform, align, drop};
  State *curState = states[0];

  while (running) {
    std::cout << "current state: " << curState->getState() << std::endl;
    int next = curState->process();
    curState = states[next];
    usleep(1000000);
  }
}
