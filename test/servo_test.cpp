// Build with:
// g++ test_gpio.cpp -o test_gpio -lmraa

#include <csignal>
#include <iostream>
#include <unistd.h>

#include "mraa.hpp"

int running = 1;

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
  mraa::Gpio servo = mraa::Pwm(3);
  servo.enable(true);

  //testing code
  while (running) {
    servo.write(0.3);

    sleep(1);
  }
}
