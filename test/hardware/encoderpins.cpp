#include "encoderpins.h"
#include "mraa.hpp"

encoderpins::encoderpins(int a_pin, int b_pin) {
	mraa::Gpio* A = new mraa::Gpio(a_pin);
	mraa::Gpio* B = new mraa::Gpio(b_pin);
}