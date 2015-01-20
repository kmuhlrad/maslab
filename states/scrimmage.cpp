//code to use for mock competition on 1/20

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

//CLEAN UP THESE
#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <typeinfo>

/*#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"
#include "servo.h"*/


//MAKE SURE THESE WORK
#include "mraa.hpp"
#include "sensordata.h"
#include "../hardware/motor.h"
#include "../hardware/gyro.h"
#include "../hardware/ir.h"

int running = 1;

double integral = 0;
double last_diff = 0.0;

struct timeval start;
struct timeval end;
struct timeval gameclock;

//PID coefficients
//work pretty well, maybe ajdust if necessary
double P = 0.05;
double I = 0.0;
double D = 0.2; //was 0.3

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

//PID drive function
void drive_straight(Motor& left, Motor& right, Gyro& gyro,
                    float desired, float estimated, float speed) {
  gettimeofday(&end, NULL);

  int diffSec = end.tv_sec - start.tv_sec;
  int diffUSec = end.tv_usec - start.tv_usec;
  float dT = (float)diffSec + 0.000001*diffUSec;

  float diff = -desired + estimated;
  integral += diff*dT;
  float derivative = diff - last_diff;
  float power = P*diff + I*integral + D*derivative;

  left.setSpeed((speed + power), 0.3);
  right.setSpeed(-(speed - power), 0.3);

  gettimeofday(&start, NULL);
  last_diff = diff;
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  gettimeofday(&start, NULL);
  gettimeofday(&gameclock, NULL);
  
  Motor left(5, 4);
  Motor right(9, 8);

  Gyro gyro;
  SensorData irs(2, 3, 6, 1, 6149.816568, 4.468768853);

  double gametime = ((double)gameclock.tv_sec - (double)start.tv_sec) + 0.000001 * (gameclock.tv_usec - start.tv_usec);

  while (running && gametime <= 180) {
    //add more cardinal directions??
    //actually update angle based on gyro

    if (irs.getDistance() < 15) {
      //drive forward
      drive_straight(left, right, gyro, 180, gyro.get_angle(), 0.2);
    }
    if (irs.readB()) {
      //drive forward
      drive_straight(left, right, gyro, 0, gyro.get_angle(), 0.2);
    }
    if (irs.readR()) {
      //drive left
      drive_straight(left, right, gyro, 270, gyro.get_angle(), 0.2);
    }
    if (irs.readL()) {
      //drive right
      drive_straight(left, right, gyro, 90, gyro.get_angle(), 0.2);
    }

    gettimeofday(&gameclock, NULL);
    gametime = ((double)gameclock.tv_sec - (double)start.tv_sec) + 0.000001 * ((double)gameclock.tv_usec - (double)start.tv_usec);
    usleep(10000);
  }

  std::cout << "finished" << std::endl;
  left.stop();
  right.stop();
}
