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
#include "encoderpins.h"

int running = 1;

int counts = 0;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

void A_handler(void* args) {
  Encoder *en = (Encoder*)args;
  en->encoderA_handler();
}

void B_handler(void* args) {
  Encoder *en = (Encoder*)args;
  en->encoderA_handler();
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  Encoder left_en = new Encoder(2, 3);
  left_en.A.isr(mraa::EDGE_BOTH, A_handler, left_en);
  left_en.B.isr(mraa::EDGE_BOTH, B_handler, left_en);

  gettimeofday(&start, NULL);
  //float init_ang = gyro.get_angle();
  //init_ang = gyro.get_angle();
  float current_ang = 0;
  int init = 0;

  float total = 0;
  while (running) {
    //NEED TO CHECK DESIRED AND ESTIMATED BASED ON GYRO OUTPUT
    //desired should come from external input: cube location or something
    //speed should depend on external input from distance sensors or camera
    //std::cout << left_en.getCounts() << std::endl;
    //drive_straight(left, right, gyro, 10.0, gyro.get_angle(), 0.1);
    usleep(10000);
  }

  //~Gyro();
}