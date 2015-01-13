//main robot file
//compile with:
//g++ gyro.cpp motor.cpp robot.cpp -o robot -lmraa
//[ADD IN OTHER FILES LATER AS NEEDED]

#include <csignal>
#include <iostream>

#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"

int running = 1;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
	// Handle Ctrl-C quit
  	signal(SIGINT, sig_handler);

  	Motor left = Motor(9, 8);
  	Motor right = Motor(5, 4);

  	mraa::Gpio sensor = mraa::Gpio(2);
  	sensor.dir(mraa::DIR_IN);

  	Gyro gyro;

	while(running) {
		if(sensor.read()) {
			left.setSpeed(0.3);
			right.setSpeed(-0.3);
			std::cout << "gyro: " << gyro.get_angle() << std::endl;
		} else {
			left.stop();
			right.stop();
		}
	}
}