/**
 * @function findContours_Demo.cpp
 * @brief Demo code to find contours in an image
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 175;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load source image and convert it to gray
  Mat src2 = imread( argv[1], 1 );
  int top = (int) (0.05*src2.rows), bottom = (int) (0.05*src2.rows);
  int left = (int) (0.05*src2.cols), right = (int) (0.05*src2.cols);
  copyMakeBorder( src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );
  /// Convert image to gray and blur it
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

/**
 * @function thresh_callback
 */
void thresh_callback(int, void* )
{
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
       double area = sqrt(contourArea(contours[i]))*0.05;
       if(area < 1) continue;
       approxPolyDP(contours[i], approxit, area, true);
//       printf("--------------------------------\nNumber of vectors in contour and aprox #%d: %d, %d \n---------------------------------",i,contours[i].size(),approxit.size());
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       if(approxit.size() ) {hexagons.push_back(approxit);drawContours( drawing, hexagons, cuenta, color, 2),cuenta++;}
     }
  printf("Number of contours, hexagons: %d, %d\n\n\n", contours.size(),cuenta);

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}


