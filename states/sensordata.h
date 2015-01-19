#ifndef SENSOR_H
#define SENSOR_H

#include "mraa.hpp"

//need to figure out how to access all of the data
//probably public methods for each of the sensors

class SensorData {
	//add all sensors we're using here
	mraa::Gpio close_IR_A;
	mraa::Gpio close_IR_B;
public:
	SensorData(int pinA, int pinB); //initialize all pin values or pass in objects directly
	void collectData(); //read all of the sensors
};

#endif