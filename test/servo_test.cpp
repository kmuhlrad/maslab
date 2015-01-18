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
  mraa::Pwm servo = mraa::Pwm(9);
  servo.enable(true);

  //testing code
  while (running) {
    float speed = 0.3;
    float output = 04 * speed + .04;
    servo.write(output);

    usleep(20000);
  }
}
