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
int counts = 0;

struct encoder {
  mraa::Gpio* A;
  mraa::Gpio* B;
};

void setMotorSpeed(mraa::Pwm& pwm, mraa::Gpio& dir, double speed) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  pwm.write(fabs(speed));
}

void stop(mraa::Pwm& pwm, mraa::Gpio& dir) {
  pwm.write(0);
  dir.write(0);
}

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

void encoder_handler(void* args) {
  mraa::Gpio* A = (*(struct encoder*)args).A;
  mraa::Gpio* B = (*(struct encoder*)args).B;
  //CHECK DIRECTION
  if (A->read() != B->read()) {
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

  //encoder input pins
  /*mraa::Gpio A = mraa::Gpio(2);
  mraa::Gpio B = mraa::Gpio(3);*/

  encoder *left_en;

  left_en->A = new mraa::Gpio(2);
  left_en->A->dir(mraa::DIR_IN);
  left_en->A->isr(mraa::EDGE_BOTH, encoder_handler, left_en);

  left_en->B = new mraa::Gpio(3);
  left_en->B->dir(mraa::DIR_IN);
  //left_en->B->isr(mraa::EDGE_BOTH, encoder_handler, left_en);

  // Set the echo handlers to receive rising or falling edges of the
  // echo pulse

  //double speed = -1.0;
  /*int last_a = left_en.A->read();
  int last_b = left_en.B->read();*/

  while (running) {
    //std::cout << "Speed: " << "0.5" << std::endl;
    /*setMotorSpeed(right_motor, right_dir, -0.1);
    setMotorSpeed(left_motor, left_dir, 0.1);*/
    //std::cout << "counts: " << counts << std::endl;
    //std::cout << "Encoder A: " << A.read() << "\t" << "Encoder B: " << B.read() << std::endl;

    usleep(80);
    /*speed += 0.1;
    if (speed > 1.0) {
      speed = -1.0;
      // Let the motor spin down
      setMotorSpeed(right_motor, right_dir, 0.0);
      sleep(2.0);
    }*/
  }
  std::cout << "running" << std::endl;
  std::cout << left_en->A->isrExit() << std::endl;
}