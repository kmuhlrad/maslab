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
#include <typeinfo>

#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"
#include "servo.h"

int running = 1;

double integral = 0;
double last_diff = 0.0;

struct timeval start;
struct timeval end;

//PID coefficients
//work pretty well, maybe ajdust if necessary
//were 0.05, 0, 0.2
double P = 0.05;
double I = 0.0;
double D = -0.2; //was 0.3

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

/*
//handler for encoder pin A on the left motor
void A_handler(void* args) {
  Encoder *en = (Encoder*)args;
  en->encoderA_handler();
}

//handler for encoder pin B on the left motor
void B_handler(void* args) {
  Encoder *en = (Encoder*)args;
  en->encoderB_handler();
}
*/

//PID drive function
void drive_straight(Motor& left, Motor& right, Gyro& gyro,
                    float desired, float estimated, float speed) {
  gettimeofday(&end, NULL);

  int diffSec = end.tv_sec - start.tv_sec;
  int diffUSec = end.tv_usec - start.tv_usec;
  float dT = (float)diffSec + 0.000001*diffUSec;

  float diff = -desired + estimated; //was - of this
  integral += diff*dT;
  float derivative = diff - last_diff;
  float power = P*diff + I*integral + D*derivative;

  //CHECK DIRECTION
  left.setSpeed(speed - power);
  right.setSpeed(speed + power);

  std::cout << "power: " << power << std::endl;

  gettimeofday(&start, NULL);
  last_diff = diff;
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  //two motor setup
  Motor left(5, 4);
  Motor right(9, 8);

  Gyro gyro;
  //IR medA = IR(1, 6149.816568, 4.468768853);

  /*Encoder *left_en = new Encoder(2, 3);
  left_en->A.isr(mraa::EDGE_BOTH, A_handler, left_en);
  left_en->B.isr(mraa::EDGE_BOTH, B_handler, left_en);*/

  //Servo servo(3);

  gettimeofday(&start, NULL);

  while (running) {
    //NEED TO CHECK DESIRED AND ESTIMATED BASED ON GYRO OUTPUT
    //desired should come from external input: cube location or something
    //speed should depend on external input from distance sensors or camera
    //std::cout << left_en.getCounts() << std::endl;
    drive_straight(left, right, gyro, 0.0, gyro.get_angle(), 0.0);
    std::cout << "gyro: " << gyro.get_angle() << std::endl;
    //servo.write(0.5);
    usleep(10000);
  }

  //~Gyro();
}
