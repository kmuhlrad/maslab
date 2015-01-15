//main robot file
//compile with:
//g++ gyro.cpp motor.cpp robot.cpp -o robot -lmraa
//[ADD IN OTHER FILES LATER AS NEEDED]

//PINS:
//1
//2 - Short range IR
//3 -
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
//A0 -
//A1 - Med range IR A
//A2 -
//A3 -
//A4 -
//A5 -

#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <typeinfo>

#include "mraa.hpp"
#include "encoder.h"
#include "gyro.h"
#include "motor.h"
#include "ultrasonic.h"
#include "ir.h"

int running = 1;

double integral = 0;

struct timeval start;
struct timeval end;

//PID coefficients
//NEED TO BE TESTED
int P = 0.001;
int I = 0.001;
int D = -0.001;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

/*int main() {
	// Handle Ctrl-C quit
	signal(SIGINT, sig_handler);

	Motor left = Motor(9, 8);
	Motor right = Motor(5, 4);

	/*mraa::Gpio sensor = mraa::Gpio(3);
	sensor.dir(mraa::DIR_IN);// (put closing comment back!!!)

	Gyro gyro;
	IR medA = IR(1, 6149.816568, 4.468768853);

  int dist = 0;
	while(running) {
    std::cout << "Distance: " << dist << " cm" << std::endl;
    for (int i = 0; i < 15; i++) {
      std::cout << medA.read() << std::endl;
      sleep(2);
    }
    dist += 5;
    std::cout << "\n" << std::endl;
    sleep(2);
	}

  ~Gyro();
}*/

//COMMENT BACK IN AND COMMENT THE OTHER MAIN OUT TO TEST PID DRIVING

void drive_straight(Motor left, Motor right, Gyro gyro,
                    float desired, float estimated, float speed) {
  //assert(-1.0 <= speed && speed <= 1.0);
  
  //set direction
  //CHECK DIRECTIONS AND THAT THIS WORKS
  /*if (speed < 0) {
    left_dir.write(1);
    right_dir.write(0);
  }
  else {
    left_dir.write(0);
    right_dir.write(1);
  }*/

  gettimeofday(&end, NULL);

  int diffSec = end.tv_sec - start.tv_sec;
  int diffUSec = end.tv_usec - start.tv_usec;
  float dT = (float)diffSec + 0.000001*diffUSec;

  float diff = desired - estimated;
  integral += diff*dT;
  float derivative = 0; //gyro.get_angular_velocity();
  float power = P*diff + I*integral + D*derivative;

  left.setSpeed(speed + power);
  right.setSpeed(-(speed - power));

  gettimeofday(&start, NULL);
}

int main() {
  //Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  //two motor setup
  Motor left = Motor(9, 8);
  Motor right = Motor(5, 4);

  Gyro gyro;

  gettimeofday(&start, NULL);
  //float init_ang = gyro.get_angle();
  //init_ang = gyro.get_angle();
  float current_ang = 0;
  int init = 0;

  float total = 0;
  while (running) {
    //NEED TO CHECK DESIRED AND ESTIMATED BASED ON GYRO OUTPUT
    //desired should come from external input: cube location or something
    //estimated should come from the current gryo angle reading
    //speed should depend on external input from distance sensors or camera
    //current_ang = gyro.get_angle() - init_ang;
    std::cout << current_ang << std::endl;
    drive_straight(left, right, gyro, -10.0, -15.0, 0.3);
    usleep(10000);
  }

  //~Gyro();
}
