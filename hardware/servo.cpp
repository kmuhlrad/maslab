#include "servo.h"
#include "shield.h"
#include "mraa.hpp"

Servo::Servo(int pwm_pin) : pwm(pwm_pin) {
  //pwm.write(0.0);
  pin = pwm_pin;
  shield = new Shield();
}

void Servo::setDegree(double deg) {
  //put this in some sort of case structure? Or just replace this with a case structure?
  //assert (deg <= 180); //ADJUST THIS 
  float value = deg / 180.0;
  float output = 0.41 * value + 0.09;
  shield.writePWM(shield.i2c, pin, output);

  /*
  MAPPING 0.09 - 0.5 to 0 - 1
  y = 0.41x + 0.09
  */
}

void Servo::write(float value) {
  shield.writePWM(shield.i2c, pin, value);
}