#include "ir.h"
#include "mraa.h"

IR::IR(int pin, double a, double b) : sensor(pin) {
	A = a;
	B = b;
}

double IR::getDistance() {
	return A / (sensor.read() + B) - 2;
}

double IR::read() {
	return sensor.read();
}