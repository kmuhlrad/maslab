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
#include <thread>

#include "mraa.hpp"
#include "../hardware/motor.h"
#include "../hardware/servo.h"
#include "../hardware/liftmech.h"
#include "../hardware/shield.h"
#include "../hardware/gyro.h"
#include "../hardware/ir.h"
#include "../hardware/piddrive.h"
#include "../vision/cubesearch.h"
#include "../vision/platfinder.h"

#include "robot_states.h"
#include "state.h"
#include "sensordata.h"

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

  Servo left_door(0);
  Servo right_door(1);

  Servo left_lift(9);
  Servo right_lift(8);
  left_lift.setDegree(shield, 160);
  right_lift.setDegree(shield, 0);

  Gyro gyro;

  mraa::Gpio topbeam(3);
  topbeam.dir(mraa::DIR_IN);

  mraa::Gpio bottombeam(9);
  bottombeam.dir(mraa::DIR_IN);

  mraa::Gpio backIR(8);
  backIR.dir(mraa::DIR_IN);

  mraa::Gpio rg(5);
  rg.dir(mraa::DIR_IN);

  IR medA = IR(2, 6149.816568, 4.468768853);
  IR medB = IR(1, 2391.189039, -0.079559138);
  IR medC = IR(0, 2683.626202, 1.265350342);

  LiftMech liftmech(&left_wheel, &right_wheel, &lift_motor,
                    &left_door, &right_door, &left_lift, &right_lift,
                    &topbeam, &bottombeam, shield);
  //was 0.015, 0, 0.4
  PIDDrive driveW(&left_wheel, &right_wheel, shield, 0.015, 0.00075, 0.4);
  PIDDrive driveA(&left_wheel, &right_wheel, shield, 0.00001, 0.0001, 0.2);
  PIDDrive driveB(&left_wheel, &right_wheel, shield, 0.00001, 0.0001, 0.1);
  PIDDrive driveC(&left_wheel, &right_wheel, shield, 0.00001, 0.0001, 0.2);

  CubeSearch cs;
  PlatformFinder pf;
  VideoCapture cap(0);

  SensorData sensors(&backIR, &rg, &medA, &medB, &medC, &gyro);

  Start *start = new Start();
  StackSearch *stack = new StackSearch(&cs, &cap, &driveW, &driveA, &driveB, &driveC);
  Drive *drive = new Drive(&cs, &cap, &driveW, &left_door, &right_door);
  Lift *lift = new Lift(&liftmech);
  PlatformSearch *platform = new PlatformSearch(&pf, &cap, &driveW, &driveA, &driveB);
  Align *align = new Align(&pf, &cap, &driveW);
  Drop *drop = new Drop(&liftmech);

  State *states[7] = {start, stack, drive, lift, platform, align, drop};
  State *curState = states[0];

  while(topbeam.read()) {
    lift_motor.setSpeed(shield, 0.25);
    std::cout << topbeam.read() << std::endl;
  }
  lift_motor.stop(shield);
  left_lift.setDegree(shield, 170-110);
  right_lift.setDegree(shield, 110);

  gettimeofday(&gameclock, NULL);
  double gametime = ((double)gameclock.tv_sec - (double)starttime.tv_sec) + 0.000001 * (gameclock.tv_usec - starttime.tv_usec);

  while (running /*&& gametime <= 180*/) {
    std::cout << "current state: " << curState->getState() << std::endl;
    int next = curState->process(sensors);
    curState = states[next];

    gettimeofday(&gameclock, NULL);
    gametime = ((double)gameclock.tv_sec - (double)starttime.tv_sec) + 0.000001 * ((double)gameclock.tv_usec - (double)starttime.tv_usec);
    //usleep(1000000);
  }
  left_wheel.stop(shield);
  right_wheel.stop(shield);
  lift_motor.stop(shield);
  cap.release();
}
