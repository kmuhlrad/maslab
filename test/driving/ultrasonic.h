#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
	double distance;
	mraa::Gpio trig;
	mraa::Gpio echo;

	void echo_handler(/*params*/);
public:
	Ultrasonic(int trig_pin, int echo_pin);
	double getDistance();
};

#endif