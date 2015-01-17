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
#include "motor.h"

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
  en->encoderB_handler();
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  Encoder *left_en = new Encoder(2, 3);
  left_en->A.isr(mraa::EDGE_BOTH, A_handler, left_en);
  left_en->B.isr(mraa::EDGE_BOTH, B_handler, left_en);

  Motor motor(5, 4); 

  while (running) {
    int counts = left_en->getCounts();
    usleep(10000);
    while (counts < 100) {
      motor.setSpeed(0.1);
    }
  }

  //~Gyro();
}
