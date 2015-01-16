#ifndef PID_H
#define PID_H

#include "mraa.hpp"
#include "motor.h"

class PIDDrive {
	double P;
	double I;
	double D;

	Motor A;
	Motor B;
	Gyro gyro;
public:
	PIDDrive(Motor a, Motor b, Gyro g, double p, double i, double d);
	void drive_straight(double desired, double estimated, double speed);
	void turn(/*param*/); //will this go here?
};

#endif