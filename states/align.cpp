#include <iostream>

#include "align.h"
#include "robot_states.h"

#include "mraa.hpp"
#include "sensordata.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../vision/platfinder.h"
#include "../hardware/piddrive.h"

Align::Align(PlatformFinder* pf, VideoCapture* vid, PIDDrive* dr) {
	state_num = ALIGN;

	drive = dr;
	platfinder = pf;
	cap = vid;

	double curAngle = 0;
}

int Align::getState() {
	return state_num;
}

int Align::process(SensorData data) {
	if (getNext(data) != state_num) {
		return getNext(data);
	} else {
		run(data);
		return state_num;
	}
}

int Align::getNext(SensorData data) {
	std::cout << "Align: getNext" << std::endl;
	if(!platfinder->findPlatform() && data.getDistanceB() < 8) {
        drive->stop();
		return DROP;
	} else {
		return ALIGN;
	}
}

void Align::run(SensorData data) {
	Mat img;
    for (int i = 0; i < 6; i++) {
	  cap->read(img);
    }
	platfinder->processImage(img);
    curAng = data.getGyroAngle();
	if (platfinder->findStack(img)) {
	    double platAng = platfinder->getAngle(img);
	    std::cout << "first curAng: " << curAng << std::endl;
	    std::cout << "first platform angle: " << platAng << std::endl;
	    std::cout << "first gyro reading: " << data.getGyroAngle() << std::endl;
	    while(data.getDistanceB() > 10) {
		    drive->drive(curAng + platAng, data.getGyroAngle(), 0.15);
		    std::cout << "curAng: " << curAng << std::endl;
		    std::cout << "platform angle: " << platAng << std::endl;
	        std::cout << "gyro reading: " << data.getGyroAngle() << std::endl;
		    std::cout << "IR: " << data.getDistanceB() << std::endl;
	    }
    }/* else {
		std::cout << "Drive: driving straight" << std::endl;
	    drive->drive(data.getGyroAngle(), data.getGyroAngle(), 0.15);
	    usleep(200000);
	}*/
}