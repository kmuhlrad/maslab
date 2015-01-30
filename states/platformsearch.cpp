#include <sys/time.h>
#include <iostream>

#include "platformsearch.h"
#include "robot_states.h"
#include "sensordata.h"
#include "mraa.hpp"

#include "opencv2/imgproc/imgproc.hpp"
#include "../hardware/piddrive.h"
#include "../vision/platfinder.h"

PlatformSearch::PlatformSearch(PlatformFinder* pf, VideoCapture* vid, PIDDrive* dr, PIDDrive* a, PIDDrive* b) {
	state_num = PLATFORMSEARCH;

	platfinder = pf;
	drive = dr;
	driveA = a;
	driveB = b;

	cap = vid;
}

int PlatformSearch::getState() {
	return state_num;
}

int PlatformSearch::process(SensorData data) {
	if (getNext(data) != state_num) {
		return getNext(data);
	} else {
		run(data);
		return state_num;
	}
}

int PlatformSearch::getNext(SensorData data) {
	Mat img;
    for(int i = 0; i < 6; i++) {
	  cap->read(img);
    }
	std::cout << "PlatformSearch: getNext" << std::endl;
	platfinder->processImage(img);
	if (platfinder->findPlatform(img)) {
        drive->stop();
		return ALIGN;
	} else {
		return PLATFORMSEARCH;
	}
}

void PlatformSearch::run(SensorData data) {
	//might only work once...
	/*if (data.getGyroAngle() > 360 || data.getGyroAngle() < -360) {
		std::cout << "StackSearch: wall following" << std::endl;
		wallFollow(data);
        sleep(200000);
        drive->stop();
	} else {*/
		std::cout << "PlatformSearch: turning" << std::endl;
		//drive->drive(data.getGyroAngle() - 5, data.getGyroAngle(), 0.0);
		drive->A->setSpeed(drive->shield, -0.25);
        drive->B->setSpeed(drive->shield, 0.25);
        usleep(300000);
        drive->stop();
	//}
}

void PlatformSearch::wallFollow(SensorData data) {
  if (data.getDistanceB() < 15) {
    driveA->stop();
    driveB->stop();
    while (data.getDistanceB() < 30) {
      driveB->A->setSpeed(driveB->shield, 0.2);
      driveB->B->setSpeed(driveB->shield, -0.2);
      std::cout << "B" << std::endl;
    }
  } else if (data.getDistanceA() > 80) {
    driveA->A->setSpeed(driveB->shield, 0.2);
    driveA->B->setSpeed(driveB->shield, -0.2);
    usleep(300000);
  } else {
    driveA->drive(15, data.getDistanceA(), 0.2);
    std::cout << "A" << std::endl;
    usleep(100000);
  }
}