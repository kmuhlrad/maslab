#ifndef GYRO_H
#define GYRO_H

#include "mraa.hpp"

class Gyro {

public:
	//external variables needed for functionality
	float angle;
	float ang_vel;
	int init = 0;

	char writeBuf[4];

	mraa::Spi* spi;
	mraa::Gpio *chipSelect;

	struct timeval tv;
	
	//constructor
	Gyro();

	//deconstructor
	//~Gyro();
	
	//class methods
	float get_angle(); //need params??
	float get_angular_velocity(); //need params??
};

#endif
