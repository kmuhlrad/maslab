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

mraa::Gpio A;
mraa::Gpio B;

Encoder::Encoder(int a_pin, int b_pin) {
  A = mraa::Gpio(a_pin);
  A.dir(mraa::DIR_IN);

  B = mraa::Gpio(b_pin);
  B.dir(mraa::DIR_IN);
}

int Encoder::getCounts() {
  //code goes here

  return counts;
}

int Encoder::getPosition() {
  //code goes here
  
  return position;
}