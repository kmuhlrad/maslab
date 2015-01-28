#ifndef SENSOR_H
#define SENSOR_H

#include "mraa.hpp"
#include "../hardware/ir.h"

//need to figure out how to access all of the data
//probably public methods for each of the sensors

class SensorData {
	//add all sensors we're using here
	mraa::Gpio* close_IR_Back;
	mraa::Gpio* rg; //red/green switch

	IR* medA;
	IR* medB;
	IR* medC;

	int dist;

public:
	SensorData(mraa::Gpio* back, mraa::Gpio* RG, IR* A, IR* B, IR* C); //initialize all pin values or pass in objects directly
	
	//return all the values
	int readBack();
	int rgswitch();

	double getDistanceA();
	double getDistanceB();
	double getDistanceC();
};

#endif