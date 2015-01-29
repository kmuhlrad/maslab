#include "sensordata.h"
#include "robot_states.h"
#include "mraa.hpp"
#include "../hardware/ir.h"
#include "../hardware/gyro.h"

SensorData::SensorData(mraa::Gpio* back, mraa::Gpio* RG, IR* A, IR* B, IR* C, Gyro* g) {
  close_IR_Back = back;
  rg = RG;

  medA = A;
  medB = B;
  medC = C;

  gyro = g;
}

int SensorData::readBack() {
  return close_IR_Back->read();
}

int SensorData::rgswitch() {
  return rg->read() + 1;
  //red = 1
  //green = 2
}

double SensorData::getDistanceA() {
  return medA->getDistance();
}

double SensorData::getDistanceB() {
  return medB->getDistance();
}

double SensorData::getDistanceC() {
  return medC->getDistance();
}

double SensorData::getGyroAngle() {
  return gyro->get_angle();
}