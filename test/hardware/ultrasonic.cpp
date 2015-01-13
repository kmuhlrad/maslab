#include <csignal>
#include <iostream>
#include <sys/time.h>

#include "ultrasonic.h"
#include "mraa.hpp"


double distance = -1.0;
mraa::Gpio trig;
mraa::Gpio echo;

Ultrasonic::Ultrasonic(int trig_pin, int echo_pin) {
  trig = mraa::Gpio(trig_pin);
  trig.dir(mraa::DIR_IN);

  echo = mraa::Gpio(echo_pin);
  echo.dir(mraa::DIR_OUT);
  echo.isr(mraa::EDGE_RISING, echo_handler, echo); //might need to make echo a pointer
}

void echo_handler(void* args) {
  // Grab end time first, for accuracy
  struct timeval end;
  gettimeofday(&end, NULL);

  mraa::Gpio* echo = (mraa::Gpio*)args;
  static struct timeval start;
  bool rising = echo->read() == 1;

  std::cout << "Echo: " << echo->read() << std::endl;
  std::cout << "Counter: " << counter << std::endl;

  counter++;
  /*if (rising) {
    std::cout << "rising!" << std::endl;
    gettimeofday(&start, NULL);
  }
  else {
    int diffSec = end.tv_sec - start.tv_sec;
    int diffUSec = end.tv_usec - start.tv_usec;
    double diffTime = (double)diffSec + 0.000001*diffUSec;

    // Speed of sound conversion: 340m/s * 0.5 (round trip)
    distance = diffTime * 170.0;

    std::cout << "Start Time: " << start.tv_sec << std::endl;
    std::cout << "End Time: " << end.tv_sec << std::endl;
    std::cout << "Diff sec: " << diffSec << std::endl;
    std::cout << "Diff usec: " << diffUSec << std::endl;
    std::cout << "Diff time: " << diffTime << std::endl;
    std::cout << "Distance: " <<  distance << "m" << std::endl;
    
  }*/
}

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  mraa::Gpio* trig = new mraa::Gpio(2);
  trig->dir(mraa::DIR_OUT);
  mraa::Gpio* echo = new mraa::Gpio(4);
  echo->dir(mraa::DIR_IN);
  // Set the echo handlers to receive rising or falling edges of the
  // echo pulse
  echo->isr(mraa::EDGE_RISING, echo_handler, echo);

  mraa::Gpio* led = new mraa::Gpio(13);
  led->dir(mraa::DIR_OUT);

  while (running) {
    // 20us trigger pulse (must be at least 10us)
    trig->write(1);
    led->write(1);
    usleep(20);
    trig->write(0);
    led->write(0);

    // Must pause at least 60ms between measurements
    usleep(500000.0);
  }
}
