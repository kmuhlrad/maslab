#ifndef WALLSEARCH_H
#define WALLSEARCH_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>

class WallSearch {
	Mat src;
	Mat src_gray;
	RNG rng(12345);

	bool wall = false;
	vector<int> centerXs;
	vector<int> centerYs;

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

	void makeBluePx(Vec3b& color); //probably delete eventually
	void makeBlue(Mat& img);

public:
	void processImage(Mat& src2);

	int getTopColor(Mat& img);
	bool findStack(Mat& img);
	vector<int> getCenterX(Mat& img);
	vector<int> getCenterY(Mat& img);
};

#endif