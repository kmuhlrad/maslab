#ifndef SHIELD_H
#define SHIELD_H

#include "mraa.hpp"

class Shield {
public:
	mraa::I2c* i2c;
	uint8_t* registers;

	Shield();

	void initPWM(mraa::I2c *i2c);
	void writePWM(mraa::I2c* i2c, int index, double duty);
};

#endif
