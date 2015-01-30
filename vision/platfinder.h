#ifndef PLATFORMFINDER_H
#define PLATFORMFINDER_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>

using namespace cv;

class PlatformFinder {
	Mat src;
	Mat src_gray;
	RNG rng;

	bool platform;
	int centerX;
	int centerY;
	double angle;

	void filterBluePx(Vec3b& color);
	void filterBlue(Mat& img);
	void filterYellowPx(Vec3b& color);
	void filterYellow(Mat& img);

	void makeBluePx(Vec3b& color);
	void makeBlue(Mat& img);
	void makeYellowPx(Vec3b& color);
	void makeYellow(Mat& img);

	void makePlatformPx(Vec3b& color);
	void makePlatform(Mat& img);

public:
	PlatformFinder();

	void processImage(Mat& src2);

	bool findPlatform(Mat& img);
	int getCenterX(Mat& img);
	int getCenterY(Mat& img);
	double getAngle(Mat& img);
};

#endif