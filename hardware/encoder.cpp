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