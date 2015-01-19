#include "sensordata.h"
#include "mraa.hpp"

SensorData::SensorData(int pinF, int pinB, int pinL, int pinR) :
  close_IR_F(pinF), close_IR_B(pinB), close_IR_L(pinL), close_IR_R(pinR) {
  
  close_IR_F.dir(mraa::DIR_IN);
  close_IR_B.dir(mraa::DIR_IN);
  close_IR_L.dir(mraa::DIR_IN);
  close_IR_R.dir(mraa::DIR_IN);
}

void SensorData::collectData() {
  //collect ALL the data!
}

int SensorData::readF() {
  return close_IR_F.read();
}

int SensorData::readB() {
  return close_IR_B.read();
}

int SensorData::readL() {
  return close_IR_L.read();
}

int SensorData::readR() {
  return close_IR_R.read();
}