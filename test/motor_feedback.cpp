#include <cassert>
#include <cmath>
#include <csignal>
#include <iostream>
#include <sys/time.h>

#include "mraa.hpp"


int running = 1;

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

void setMotorSpeed(mraa::Pwm& pwm, mraa::Gpio& dir, double speed) {
  assert(-1.0 <= speed && speed <= 1.0);
  if (speed < 0) {
    dir.write(1);
  }
  else {
    dir.write(0);
  }
  pwm.write(fabs(speed));
}

static double distance = -1.0;
void echo_handler(void* args) {
  // Grab end time first, for accuracy
  struct timeval end;
  gettimeofday(&end, NULL);

  mraa::Gpio* echo = (mraa::Gpio*)args;
  static struct timeval start;
  bool rising = echo->read() == 1;
  if (rising) {
    gettimeofday(&start, NULL);
  }
  else {
    int diffSec = end.tv_sec - start.tv_sec;
    std::cout << "Diff sec: " << diffSec << std::endl;
    int diffUSec = end.tv_usec - start.tv_usec;
    std::cout << "Diff usec: " << diffUSec << std::endl;
    double diffTime = (double)diffSec + 0.000001*diffUSec;
    std::cout << "Diff time: " << diffTime << std::endl;
    // Speed of sound conversion: 340m/s * 0.5 (round trip)
    std::cout << "Distance: " <<  diffTime * 170.0 << "m" << std::endl;
    distance = diffTime * 170.0;
  }
}

bool found_object(mraa::Gpio pin) {
  return pin.read();
}

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  // short-range IR pin
  mraa::Gpio sensor = mraa::Gpio(2);
  trig.dir(mraa::DIR_IN);

  // Motor pins
  mraa::Pwm left_motor = mraa::Pwm(9);
  left_motor.write(0.0);
  left_motor.enable(true);
  mraa::Gpio left_dir = mraa::Gpio(8);
  left_dir.dir(mraa::DIR_OUT);
  left_dir.write(0);

  mraa::Pwm right_motor = mraa::Pwm(5);
  right_motor.write(0.0);
  right_motor.enable(true);
  mraa::Gpio right_dir = mraa::Gpio(4);
  right_dir.dir(mraa::DIR_OUT);
  right_dir.write(0);
  
  while (running) {
    // 20us trigger pulse (must be at least 10us)
    trig.write(1);
    usleep(20);
    trig.write(0);

    if (found_object(sensor))
    if (distance > 0.2 && distance < 1.0) {
      std::cout << "Setting motor speed: " << 1.0 - distance << std::endl;
      setMotorSpeed(motPwm, motDir, 1.0 - distance);
    }
    else {
      setMotorSpeed(motPwm, motDir, 0.0);
    }

    // Must pause at least 60ms between measurements
    usleep(200000.0);
  }
}

