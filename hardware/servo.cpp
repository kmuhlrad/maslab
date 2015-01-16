// Compile with:
// g++ motor.cpp -o motor -lmraa
// Controls a motor through a range of speeds using the Cytron motor controller
// Pwm on pin 9, and dir on pin 8.

//new added comment

#include <cassert>
#include <cmath>
#include <iostream>

#include "motor.h"
#include "mraa.hpp"

Servo::Servo(int pwm_pin) : pwm(pwm_pin) {
  //pwm.write(0.0);
  pwm.enable(true);
}

void Servo::setDegree(int deg) {
  //put this in some sort of case structure? Or just replace this with a case structure?
  assert (deg <= 180); //ADJUST THIS 
  float value = deg / 180.0; //ADJUST THIS TOO
  pwm.write(value);
}

//maybe delete??
void Servo::stop() {
  pwm.write(pwm.read());
}