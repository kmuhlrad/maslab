#include "sensordata.h"
#include "robot_states.h"
#include "mraa.hpp"

SensorData::SensorData(mraa::Gpio* back, mraa::Gpio* RG, IR* A, IR* B, IR* C) {
  close_IR_Back = back;
  rg = RG;

  medA = A;
  medB = B;
  medC = C;
}

int SensorData::readBack() {
  return close_IR_Back.read();
}

int SensorData::rgswitch() {
  return rg.read() + 1;
  //red = 1
  //green = 2
}

double SensorData::getDistanceA() {
  return medA.getDistance();
}

double SensorData::getDistanceB() {
  return medB.getDistance();
}

double SensorData::getDistanceC() {
  return medC.getDistance();
}