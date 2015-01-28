#ifndef CUBESEARCH_H
#define CUBESEARCH_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <vector>

using namespace cv;

class CubeSearch {
	Mat src;
	Mat src_gray;
	RNG rng;

	bool stack;
	vector<int> centerXs;
	vector<int> centerYs;
	vector<double> angles;

	void filterGreenPx(Vec3b& color);
	void filterGreen(Mat& img);
	void filterRedPx(Vec3b& color);
	void filterRed(Mat& img);

	//EVENTUALLY REMOVE
	void filterBluePx(Vec3b& color);
	void filterBlue(Mat& img);
	void filterYellowPx(Vec3b& color);
	void filterYellow(Mat& img);
	///////////////////

	void filterStackPx(Vec3b& color);
	void filterStack(Mat& img);

	void makeRedPx(Vec3b& color); //probably delete eventually
	void makeRed(Mat& img);
	void makeStackPx(Vec3b& color);
	void makeStack(Mat& img);

public:
	CubeSearch();

	void processImage(Mat& src2);

	int getTopColor(Mat& img);
	bool findStack(Mat& img);
	vector<int> getCenterX(Mat& img);
	vector<int> getCenterY(Mat& img);
	vector<double> getAngle(Mat& img);
};

#endif