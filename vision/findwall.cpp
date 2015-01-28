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

bool wall = false;

/// Function header
void thresh_callback(int, void* );

//MY NEW CODE
//gb: 1.02, 1.04, 1.02
//gr: 1.04, 0.98, 1.02
void filterGreenPx(Vec3b& color) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[1] < color[0]*1.09 || color[1] < color[2]*1.02){
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

//rg: 1.3
//rb: 0
void filterRedPx(Vec3b& color) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[2] < color[1]*1.3){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterRed(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterRedPx(img.at<Vec3b>(Point(x, y)));
}

//br: 1.2, 1.5?
//bg: 1.2
void filterBluePx(Vec3b& color) { //bgr
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

//rg: 0
//rb: 1.8
void filterYellowPx(Vec3b& color) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[2] < color[0]*1.8){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterYellow(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterYellowPx(img.at<Vec3b>(Point(x, y)));
}

void makeBluePx(Vec3b& color) { //bgr
  if(color[0] > color[1]*1.2 && color[0] > color[2]*1.2){
    color[2] = 0;
    color[1] = 0;
    color[0] = 255;
  }
}

void makeBlue(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makeBluePx(img.at<Vec3b>(Point(x, y)));
}

void makeYellowPx(Vec3b& color) {//bgr
  if(color[2] > color[0]*1.8){
    color[2] = 255;
    color[1] = 255;
    color[0] = 0;
  }
}

void makeYellow(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeYellowPx(img.at<Vec3b>(Point(x, y)));
}

void findWallsPx(Vec3b& color) { //bgr
  if(color[2] > color[0]*1.8){
    color[2] = 255;
    color[1] = 255;
    color[0] = 0;
  } else if(color[0] > color[1]*1.2 && color[0] > color[2]*1.2){
    color[2] = 0;
    color[1] = 0;
    color[0] = 255;
  } else {
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void findWalls(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        findWallsPx(img.at<Vec3b>(Point(x, y)));
}

int main(int, char** argv) {
  /// Load source image and convert it to gray
  Mat src2 = imread(argv[1], 1);
  int top = (int) (0.05*src2.rows), bottom = (int) (0.05*src2.rows);
  int left = (int) (0.05*src2.cols), right = (int) (0.05*src2.cols);
  //copyMakeBorder( src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );
  
  findWalls(src2);

  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  dilate( src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  dilate(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  copyMakeBorder( src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  const char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

  //createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}

void thresh_callback(int, void*) {
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  vector<vector<Point> > hexagons;
  vector<Point> approx;

  findContours(src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  /// Draw contours
  Mat drawing = Mat::zeros(src_gray.size(), CV_8UC3);
  int count = 0;
  double last_area = 0;
  Rect bounding;

  for (size_t i = 0; i < contours.size(); i++) {
    double area = sqrt(contourArea(contours[i]))*0.05;

    //skip small particles or duplicate 
    if (20*area < 120 || ((last_area - 2) < 20*area  && 20*area < (last_area + 2))) continue;

    approxPolyDP(contours[i], approx, area, true);
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    
    if (approx.size()) {
      last_area = 20*area;
      hexagons.push_back(approx);
      drawContours(drawing, hexagons, count, color, 2);
      bounding = boundingRect(approx);
      
      Point center((bounding.x + bounding.width/2), (bounding.y + bounding.height/2));

      //bounding box
      rectangle(drawing, bounding.tl(), bounding.br(), color, 2, 8, 0);

      //center point
      circle(drawing, center, 2, color, 2, 8, 0);

      printf("Center: (%d, %d) \n", center.x, center.y);

      wall = true;
      count++;
    }
  }
  //Show output picture in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}