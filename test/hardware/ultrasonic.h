#ifndef ULTRASONIC_H
#define ULTRASONIC_H

class Ultrasonic {
	double distance;
	mraa::Gpio trig;
	mraa::Gpio* echo;

	void echo_handler(void* args);
public:
	Ultrasonic(int trig_pin, int echo_pin);
	double getDistance();
	void pulse(int us);
	~Ultrasonic();
};

#endif