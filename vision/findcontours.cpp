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

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 175;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

//gb: 1.02, 1.04, 1.02
//gr: 1.04, 0.98, 1.02
void filterGreenPx(Vec3b& color) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[1] < color[0]*1.02 || color[1] < color[2]*1){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterGreen(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterGreenPx(img.at<Vec3b>(Point(x, y)));
}

//br: 1.2, 1.5?
//bg: 1.2
void filterBluePx(Vec3b& color) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[0] < color[1]*1.2 || color[0] < color[2]*1.2){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  } else {
    color[2] = 255;
    color[1] = 255;
    color[0] = 255;
  }
}

void filterBlue(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterBluePx(img.at<Vec3b>(Point(x, y)));
}

/**
 * @function main
 */
int main( int, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  filterBlue(src);

  erode(src, src, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  dilate( src, src, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  dilate(src, src, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  erode(src, src, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

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

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  printf("Number of contours: %d\n\n\n", (int)contours.size());
  for( size_t i = 0; i< contours.size(); i++ )
     {
       printf("--------------------------------\nNumber of vectors in contour #%d: %d \n---------------------------------",(int)i,(int)contours[i].size());
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, (int)i, color, -1, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}


