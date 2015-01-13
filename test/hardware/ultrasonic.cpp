#include <csignal>
#include <iostream>
#include <sys/time.h>

#include "ultrasonic.h"
#include "mraa.hpp"


double distance = -1.0;

Ultrasonic::Ultrasonic(int trig_pin, int echo_pin) : trig(trig_pin), echo(echo_pin) {
  trig.dir(mraa::DIR_IN);
  
  echo->dir(mraa::DIR_OUT);
  echo->isr(mraa::EDGE_RISING, echo_handler, echo); //might need to make echo a pointer
}

void Ultrasonic::pulse(int us) {
  assert(us >= 10);
  trig.write(1);
  usleep(us);
  trig.write(0);
}

void Ultrasonic::echo_handler(void* args) {
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

Ultrasonic::~Ultrasonic() {
  delete echo;
}