//main robot file
//compile with:
//g++ gyro.cpp motor.cpp robot.cpp -o robot -lmraa
//[ADD IN OTHER FILES LATER AS NEEDED]

//PINS:
//1
//2 - Short range IR
//3 - Med range IR
//4 - Right wheel dir
//5 - Right wheel pwm
//6
//7 - DON'T USE!!!!
//8 - Left wheel dir
//9 - Left wheel pwm
//10 - Gyro CS
//11 - Gyro MOSI
//12 - Gyro MISO
//13 - Gyro SCLK

#include <csignal>
#include <iostream>

#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"

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

  	/*mraa::Gpio sensor = mraa::Gpio(3);
  	sensor.dir(mraa::DIR_IN);*/

  	Gyro gyro;
  	IR medA = IR(1, 5860.550742, 4.236506397);

	while(running) {
		std::cout << "IR: " << medA.getDistance() << std::endl;
	}
}