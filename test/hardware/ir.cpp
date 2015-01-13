#include "ir.h"
#include "mraa.h"

mraa::Aio sensor;

IR::IR(int pin, double a, double b) : sensor(pin) {
	A = a;
	B = b;
}

double IR::getDistance() {
	return A / (sensor.read() - B);
}