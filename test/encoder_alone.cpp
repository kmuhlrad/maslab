// Compile with:
// g++ encoder.cpp -o encoder -lmraa

//Theoretically every time they are both 1 they have gone the same amount of distance
//so that can be the check
//This can be tested experimentally, but if I update every 2.68 ms it should be about right
//I'll try with 2.5 and see if I get a better wave than with 100...
//3 if too much
//then adjust in between if needed

#include <cassert>
#include <cmath>
#include <csignal>
#include <iostream>

#include "mraa.hpp"

int running = 1;
int counts = 0; //total number of encoder counts

//structure that holds two pointers to encoder pins to pass into an isr handler
struct encoder {
  mraa::Gpio* A;
  mraa::Gpio* B;
};

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

//function that triggers when A changes
void encoderA_handler(void* args) {
  mraa::Gpio* A = (*(struct encoder*)args).A;
  mraa::Gpio* B = (*(struct encoder*)args).B;
  if (A->read() != B->read()) {
    counts++;
  } else {
    counts--;
  }
  std::cout << counts << std::endl;
}

//function that trigger when B changes
void encoderB_handler(void* args) {
  mraa::Gpio* A = (*(struct encoder*)args).A;
  mraa::Gpio* B = (*(struct encoder*)args).B;
  if (A->read() == B->read()) {
    counts++;
  } else {
    counts--;
  }
  std::cout << counts << std::endl;
}

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);
  
  //two motor setup
  mraa::Pwm left_motor = mraa::Pwm(9);
  left_motor.write(0.0);
  left_motor.enable(true);
  mraa::Gpio left_dir = mraa::Gpio(8);
  left_dir.dir(mraa::DIR_OUT);
  left_dir.write(0);

  mraa::Pwm right_motor = mraa::Pwm(5);
  right_motor.write(0.0);
  right_motor.enable(true);
  mraa::Gpio right_dir = mraa::Gpio(4);
  right_dir.dir(mraa::DIR_OUT);
  right_dir.write(0);

  //encoder structure pointer to pass into the handlers
  encoder *left_en = new encoder;

  left_en->A = new mraa::Gpio(2);
  left_en->A->dir(mraa::DIR_IN);
  left_en->A->isr(mraa::EDGE_BOTH, encoderA_handler, left_en);

  left_en->B = new mraa::Gpio(3);
  left_en->B->dir(mraa::DIR_IN);
  left_en->B->isr(mraa::EDGE_BOTH, encoderB_handler, left_en);

  while (running) {
    usleep(80);
  }

  left_en->A->isrExit();
}