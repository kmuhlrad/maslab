#include <csignal>
#include <iostream>
#include <cassert>
#include <cmath>
#include <sys/time.h>
#include <typeinfo>

#include "mraa.hpp"
#include "gyro.h"
#include "motor.h"
#include "piddrive.h"
#include "shield.h"
#include "ir.h"

#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/cubesearch.h"

int running = 1;

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("closing spi nicely\n");
    running = 0;
  }
}

int main() {
  CubeSearch cs;
  Mat img = imread("../fieldpictures/rgr1.jpg");
  
  while (running) {
    cs.processImage(img);
  }
}
