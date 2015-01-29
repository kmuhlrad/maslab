#ifndef PID_H
#define PID_H

#include "mraa.hpp"
#include "motor.h"

class PIDDrive {
	double P;
	double I;
	double D;

	Shield* shield;

	double integral;
	double last_diff;

	struct timeval start;
	struct timeval end;
public:
	Motor* A;
	Motor* B;
	
	PIDDrive(Motor* a, Motor* b, Shield* s,
			 double p, double i, double d);
	void drive(double desired, double estimated, double speed);
	void stop();
};

#endif