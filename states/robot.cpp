//main robot file
//compile with:
//g++ gyro.cpp motor.cpp robot.cpp -o robot -lmraa
//[ADD IN OTHER FILES LATER AS NEEDED]

//PINS:

//DIO:
//0 - Left wheel dir
//1 - Lift motor dir
//2 - Right wheel dir
//3 - Top breakbeam
//4 - 
//5 - 
//6 - 
//7 - DON'T USE!!!!
//8 - Back close IR
//9 - Bottom breakbeam
//10 - Gyro CS
//11 - Gyro MOSI
//12 - Gyro MISO
//13 - Gyro SCLK

//A0 - Med range IR C
//A1 - Med range IR B
//A2 - Med range IR A
//A3 -
//A4 - DON'T USE
//A5 - DON'T USE

//PWM (SWITCH AROUND)
//0 - Left door servo
//1 - Right door servo
//2 - 
//3 - 
//4 - Right wheel PWM
//5 - 
//6 - 
//7 - 
//8 - Right lift servo
//9 - Left lift servo
//10 - 
//11 - 
//12 - Lift motor PWM
//13 - 
//14 - 
//15 - Left wheel PWM

#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <unistd.h>

#include "mraa.hpp"
#include "../hardware/motor.h"
#include "../hardware/servo.h"
#include "../hardware/liftmech.h"
#include "../hardware/shield.h"

#include "robot_states.h"
#include "state.h"

#include "start.h"
#include "stacksearch.h"
#include "drive.h"
#include "lift.h"
#include "platformsearch.h"
#include "align.h"
#include "drop.h"



int running = 1;

struct timeval gameclock;
struct timeval starttime;

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

  Motor left_wheel(15, 0);
  Motor right_wheel(4, 2);
  Motor lift_motor(12, 1);

  Servo left_door(1);
  Servo right_door(0);

  Servo left_lift(9);
  Servo right_lift(8);

  mraa::Gpio topbeam(3);
  topbeam.dir(mraa::DIR_IN);

  mraa::Gpio bottombeam(9);
  bottombeam.dir(mraa::DIR_IN);

  LiftMech liftmech(&left_wheel, &right_wheel, &lift_motor,
                    &left_door, &right_door, &left_lift, &right_lift,
                    &topbeam, &bottombeam, shield);

  Start *start = new Start();
  StackSearch *stack = new StackSearch();
  Drive *drive = new Drive();
  Lift *lift = new Lift(&liftmech);
  PlatformSearch *platform = new PlatformSearch();
  Align *align = new Align();
  Drop *drop = new Drop(&liftmech);

  State *states[7] = {start, stack, drive, lift, platform, align, drop};
  State *curState = states[0];

  gettimeofday(&gameclock, NULL);
  double gametime = ((double)gameclock.tv_sec - (double)starttime.tv_sec) + 0.000001 * (gameclock.tv_usec - starttime.tv_usec);

  while (running /*&& gametime <= 180*/) {
    std::cout << "current state: " << curState->getState() << std::endl;
    int next = curState->process();
    curState = states[next];

    gettimeofday(&gameclock, NULL);
    gametime = ((double)gameclock.tv_sec - (double)starttime.tv_sec) + 0.000001 * ((double)gameclock.tv_usec - (double)starttime.tv_usec);
    usleep(1000000);
  }
}
