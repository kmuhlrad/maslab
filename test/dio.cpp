// Build with:
// g++ test_gpio.cpp -o test_gpio -lmraa

#include <csignal>
#include <iostream>
#include <unistd.h>

#include "mraa.hpp"

int running = 1;

/*
void on(mraa::Gpio pin) {
  pin.write(1);
}

void off(mraa::Gpio pin) {
  pin.write(0);
}*/

void sig_handler(int signo)
{
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
  // Handle Ctrl-C quit
  signal(SIGINT, sig_handler);

  // LED is connected to pin 13
  mraa::Gpio gpio = mraa::Gpio(13);
  gpio.dir(mraa::DIR_OUT);

  // short range IR sensor
  mraa::Gpio sr_ir = mraa::Gpio(12);
  sr_ir.dir(mraa::DIR_IN);

  //testing code
  while (running) {
    //this should do the same thing as below
    /*
    on(gpio);
    sleep(1);
    off(gpio);
    sleep(1);*/


    std::cout << "IR sensor: " << sr_ir.read() << std::endl;
    //old code - eventually delete
    printf("Gpio high\n");
    gpio.write(1);
    sleep(1);
    printf("Gpio low\n");
    gpio.write(0);
    sleep(1);
  }
}
