#ifndef SENSOR_H
#define SENSOR_H

#include "mraa.hpp"
#include "../hardware/ir.h"

//need to figure out how to access all of the data
//probably public methods for each of the sensors

class SensorData {
	//add all sensors we're using here
	mraa::Gpio close_IR_B;
	mraa::Gpio close_IR_R;
	mraa::Gpio close_IR_L;

	IR medA;

	//sensor values
	int b;
	int r;
	int l;

	int dist;

public:
	SensorData(int pinL, int pinB, int pinR, int pinIR, double a, double b); //initialize all pin values or pass in objects directly
	void collectData(); //read all of the sensors
	
	//return all the values
	int readB();
	int readR();
	int readL();

	double getDistance();
};

#endif