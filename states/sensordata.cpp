#include "sensordata.h"
#include "mraa.hpp"

SensorData::SensorData(int pwm_pin) : pwm(pwm_pin) {
  pwm.write(0.0);
  pwm.enable(true);
}

void SensorData::collectData() {
  //collect ALL the data!
}