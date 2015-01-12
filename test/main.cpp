// Build with:
// g++ test_gpio.cpp -o test_gpio -lmraa

#include <csignal>
#include <iostream>
#include <unistd.h>

#include "add.h"
#include "mraa.hpp"

int running = 1;
int my_sum = 0;

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

  //testing code
  while (running) {
    Add test;
    test.set_a(2);
    test.set_b(6);
    my_sum = test.two_sum();
    gpio.write(1);
    std::cout << my_sum << std::endl;
  }
}
