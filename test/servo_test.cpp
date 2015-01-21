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
  mraa::Pwm servo1 = mraa::Pwm(9);
  servo1.enable(true);

  mraa::Pwm servo2 = mraa::Pwm(3);
  servo2.enable(true);

  float speed1 = 90. / 180.;
  float speed2 = 90. / 180.;
  //testing code
  while (running) {
    float output1 = 0.41 * speed1 + .09;
    float output2 = 0.41 * speed2 + .09;
    servo1.write(output1);
    servo2.write(output2);
    //speed += 0.01;
    usleep(50000);
  }
}
