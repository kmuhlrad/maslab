#ifndef SENSOR_H
#define SENSOR_H

#include "mraa.hpp"

//need to figure out how to access all of the data
//probably public methods for each of the sensors

class SensorData {
	//add all sensors we're using here
	mraa::Gpio close_IR_F;
	mraa::Gpio close_IR_B;
	mraa::Gpio close_IR_L;
	mraa::Gpio close_IR_R;

	//sensor values
	int f;
	int b;
	int l;
	int r;

public:
	SensorData(int pinF, int pinB, int pinL, int pinR); //initialize all pin values or pass in objects directly
	void collectData(); //read all of the sensors
	
	//return all the values
	int readF();
	int readB();
	int readL();
	int readR();
};

#endif