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

int thresh = 175;
int max_thresh = 255;
RNG rng(12345);
const char* source_window = "Source";
/// Function header
void thresh_callback(int, void* );

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load source image and convert it to gray

  /// Convert image to gray and blur it

  /// Create Window

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
   char escapeKey;
VideoCapture cap(0);
  if(!cap.isOpened()) return;
  do{
//  src = imread( argv[1], 1 );
  Mat src, src_gray;
  cap >> src;
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

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

       approxPolyDP(contours[i], approxit, sqrt(contourArea(contours[i]))*0.05, true);
//       printf("--------------------------------\nNumber of vectors in contour and aprox #%d: %d, %d \n---------------------------------",i,contours[i].size(),approxit.size());
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       if(approxit.size() == 6) {hexagons.push_back(approxit);drawContours( drawing, hexagons, cuenta, color, 2),cuenta++;}
     }
  printf("Number of contours, hexagons: %d, %d\n\n\n", contours.size(),cuenta);

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
   escapeKey=cvWaitKey(10);
  }while(escapeKey != 'q');
cap.release();
}


