// SPI pins are:
// - IO10: CS
// - IO11: MOSI
// - IO12: MISO
// - IO13: SCLK

#include <unistd.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>

#include "gyro.h"
#include "mraa.hpp"

#define MS 1000

#define GYRO_DATA_OKAY_MASK 0x0C000000
#define GYRO_DATA_OKAY 0x04000000

float angle = 0.0;
float ang_vel = 0.0;
int init = 0;
char writeBuf[4];

mraa::Spi* spi;
mraa::Gpio *chipSelect = new mraa::Gpio(10);
//CHECK SCOPE OF VARIABLES

struct timeval tv;

Gyro::Gyro() {
  chipSelect->dir(mraa::DIR_OUT);
  chipSelect->write(1);

  spi = new mraa::Spi(0);
  spi->bitPerWord(32);

  char rxBuf[2];
  
  unsigned int sensorRead = 0x20000000;
  writeBuf[0] = sensorRead & 0xff;
  writeBuf[1] = (sensorRead >> 8) & 0xff;
  writeBuf[2] = (sensorRead >> 16) & 0xff;
  writeBuf[3] = (sensorRead >> 24) & 0xff;

  float total = 0;
  struct timeval tv;
  init = 0;
}

float Gyro::get_angle() {
  chipSelect->write(0);
  char* recv = spi->write(writeBuf, 4);
  chipSelect->write(1);

  if (recv != NULL) {
    unsigned int recvVal = ((uint8_t) recv[3] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[2] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[1] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[0] & 0xFF);
    
    // Sensor reading
    short reading = (recvVal >> 10) & 0xffff;

    if (init) {
      unsigned long long ms = (unsigned long long)(tv.tv_sec)*1000 +
        (unsigned long long)(tv.tv_usec) / 1000;

      gettimeofday(&tv, NULL);

      ms -= (unsigned long long)(tv.tv_sec)*1000 +
        (unsigned long long)(tv.tv_usec) / 1000;

      int msi = (int)ms;
      float msf = (float)msi;
      float ang_vel = (float)reading / 80.0;
      angle += -0.001 * msf * (ang_vel);

      return angle;
    }
    else { //init == 0
      init = 1;
      gettimeofday(&tv, NULL);
      return 0;
    }
  }
  else {
    printf("No recv\n"); //no data
    return 100000.0;
  }
}

float Gyro::get_angular_velocity() {
  chipSelect->write(0);
  //char* recv = spi->write(writeBuf, 4);
  chipSelect->write(1);
  //printf("%x %x %x %x\r\n", recv[0], recv[1], recv[2], recv[3]);

  /*if (recv != NULL) {
    unsigned int recvVal = ((uint8_t) recv[3] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[2] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[1] & 0xFF);
    recvVal = (recvVal << 8) | ((uint8_t)recv[0] & 0xFF);
    
    // Sensor reading
    short reading = (recvVal >> 10) & 0xffff;

    if (init) {
      unsigned long long ms = (unsigned long long)(tv.tv_sec)*1000 +
        (unsigned long long)(tv.tv_usec) / 1000;

      gettimeofday(&tv, NULL);

      ms -= (unsigned long long)(tv.tv_sec)*1000 +
        (unsigned long long)(tv.tv_usec) / 1000;

      int msi = (int)ms;
      float msf = (float)msi;
      float ang_vel = (float)reading / 80.0;

      return ang_vel;
    }
    else { //init == 0
      init = 1;
      gettimeofday(&tv, NULL);
      return 0;
    }
  }
  else {
    printf("No recv\n"); //no data
    return 10000.0;
  }*/
    return 0;
}

Gyro::~Gyro() {
  delete spi;
}