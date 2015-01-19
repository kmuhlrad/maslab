#include "servo.h"
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

  /*
  MAPPING 0.09 - 0.5 to 0 - 1
  y = 0.41x + 0.09
  */
}

void Servo::write(float value) {
  pwm.write(value);
}

//maybe delete??
void Servo::stop() {
  pwm.write(pwm.read());
}