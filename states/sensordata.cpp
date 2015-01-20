#include "sensordata.h"
#include "robot_states.h"
#include "mraa.hpp"

SensorData::SensorData(int pinB, int pinR, int pinL, int pinIR, double a, double b) :
  close_IR_B(pinB), close_IR_R(pinR), close_IR_L(pinL), medA(pinIR, a, b) {
  
  close_IR_B.dir(mraa::DIR_IN);
  close_IR_R.dir(mraa::DIR_IN);
  close_IR_L.dir(mraa::DIR_IN);
}

void SensorData::collectData() {
  //collect ALL the data!
  //honestly maybe delete...
  //wait until I know more about vision
}

int SensorData::readB() {
  return close_IR_B.read();
}

int SensorData::readR() {
  return close_IR_R.read();
}

int SensorData::readL() {
  return close_IR_L.read();
}

double SensorData::getDistance() {
  return medA.getDistance();
}