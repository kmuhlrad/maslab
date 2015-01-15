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

#include "encoder.h"
#include "mraa.hpp"

struct encoder {
	mraa::Gpio* A;
	mraa::Gpio* B;
};

Encoder::Encoder(int a_pin, int b_pin) {
  encoder *en = new encoder;

  en->A = new mraa::Gpio(a_pin);
  en->A->dir(mraa::DIR_IN);
  en->A->isr(mraa::EDGE_BOTH, encoderA_handler, en);

  en->B = new mraa::Gpio(b_pin);
  en->B->dir(mraa::DIR_IN);
  en->B->isr(mraa::EDGE_BOTH, encoderB_handler, en);

  counts = 0;
}

int Encoder::getCounts() {
	return counts;
}

void Encoder::resetCounts() {
	counts = 0;
}

//function that triggers when A changes
void encoderA_handler(void* args) {
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

//function that trigger when B changes
void encoderB_handler(void* args) {
  mraa::Gpio* A = (*(struct encoder*)args).A;
  mraa::Gpio* B = (*(struct encoder*)args).B;
  //CHECK DIRECTION
  if (A->read() == B->read()) {
    counts++;
  } else {
    counts--;
  }
  std::cout << counts << std::endl;
}

//maybe delete
int Encoder::getPosition() {
  //code goes here
  double position = 0;

  return position;
}

Encoder::~Encoder() {
  en->A->isrExit();
  en->B->isrExit();
}