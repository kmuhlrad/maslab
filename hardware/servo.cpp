#include "servo.h"
#include "shield.h"
#include "mraa.hpp"

Servo::Servo(int pwm_pin) {
  //pwm.write(0.0);
  pin = pwm_pin;
}

void Servo::setDegree(Shield* shield, double deg) {
  //put this in some sort of case structure? Or just replace this with a case structure?
  //assert (deg <= 180); //ADJUST THIS 
  float value = deg / 180.0;
  float output = 0.079 * value + 0.021;
  shield->writePWM(pin, output);

  /*
  MAPPING 0.09 - 0.5 to 0 - 1
  y = 0.41x + 0.09

  //new mapping 0.07x + 0.03
  */
}

void Servo::write(Shield* shield, float value) {
  shield->writePWM(pin, value);
}