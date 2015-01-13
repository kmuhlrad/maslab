#ifndef IR_H
#define IR_H

#include "mraa.hpp"

class IR {
	mraa::Aio sensor;
	double A;
	double B;
public:
	IR(int pin, double a, double b);
	double getDistance();
};

#endif