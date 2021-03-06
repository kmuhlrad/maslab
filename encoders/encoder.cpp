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

Encoder::Encoder(int a_pin, int b_pin) : A(a_pin), B(b_pin) {
  A.dir(mraa::DIR_IN);

  B.dir(mraa::DIR_IN);

  counts = 0;
}

int Encoder::getCounts() {
	return counts;
}

void Encoder::resetCounts() {
	counts = 0;
}

//function that triggers when A changes
void Encoder::encoderA_handler() {
  //CHECK DIRECTION
  if (A.read() != B.read()) {
    counts++;
  } else {
    counts--;
  }
}

//function that trigger when B changes
void Encoder::encoderB_handler() {
  //CHECK DIRECTION
  if (A.read() == B.read()) {
    counts++;
  } else {
    counts--;
  }
}