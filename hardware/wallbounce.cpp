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

  Gyro gyro;

  IR medA = IR(1, 6149.816568, 4.468768853);

  //was 0.015, 0, 0.4
  PIDDrive drive(&left_motor, &right_motor, shield, 0.05, 0, 0.2);

  int straight = 0;
  int turning = 0;
  double curAngle = gyro.get_angle();
  /*double startDist = medA.getDistance();
  double dist[5] = {startDist, startDist, startDist, startDist, startDist};
  double avg = startDist;
  double sum = 0;
*/
  while (running) {
    /*sum = 0;
    for (int i = 1; i <= 4; i++) {
      dist[i-1] = dist[i];
    }
    dist[4] = medA.getDistance();
    for (int i = 0; i < 5; i++) {
       sum +=  dist[i];
    }
    avg = sum / 5.;
    */
    std::cout << "sensor: " << medA.getDistance() << std::endl;
    //std::cout << "avg: " << avg << std::endl;

    if (medA.getDistance() < 30) {
      if (turning == 0) {
        curAngle = gyro.get_angle();
      }
      turning++;
      drive.drive(curAngle + 90, gyro.get_angle(), .25); //turn away from wall
      straight = 0;
      sleep(.75);
      std::cout << "turning " << "angle: " << curAngle << std::endl;
    } else {
      turning = 0;
      if (straight == 0) {
        curAngle = gyro.get_angle();
      }
      straight++;
      drive.drive(curAngle, gyro.get_angle(), 0.25); //keep driving straight
      std::cout << "straight\t" << "angle: " << curAngle <<  std::endl;
      //sleep(0.25);
    }

    /*if (avg < 30) {
      drive.drive(gyro.get_angle(), gyro.get_angle(), -.25);
    } else {
      drive.drive(gyro.get_angle(), gyro.get_angle(), 0.25);
    }*/
    usleep(30000);
  }
}
