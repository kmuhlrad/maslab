
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int thresh = 0;
RNG rng(12345);


Mat detectShapes(Mat& src2){
  Mat src,src_gray;
 
 int top = (int) (0.05*src2.rows), bottom = (int) (0.05*src2.rows);
  int left = (int) (0.05*src2.cols), right = (int) (0.05*src2.cols);
 copyMakeBorder( src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );
 
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  vector<vector<Point> > hexagons;
  vector<Point> approxit;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  int cuenta = 0;
  for( size_t i = 0; i< contours.size(); i++ )
     {
       double area = sqrt(contourArea(contours[i])), perimeter = arcLength(contours[i],true);
//        if(area < 20) continue;
       approxPolyDP(contours[i], approxit, area*0.05 , true);
//       printf("--------------------------------\nNumber of vectors in contour and aprox #%d: %d, %d \n---------------------------------",i,contours[i].size(),approxit.size());
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       if(approxit.size() <= 6) {hexagons.push_back(approxit);drawContours( drawing, hexagons, cuenta, color, 2),cuenta++;}
     }
  printf("Number of contours, hexagons: %d, %d\n\n\n", contours.size(),cuenta);

   return drawing;
}

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);

    namedWindow("Original",1);
    for(;;)
    {
        Mat src;
        cap >> src; // get a new frame from camera
	
	edges = detectShapes(src);

        imshow("edges", edges);
	imshow("Original", src);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


