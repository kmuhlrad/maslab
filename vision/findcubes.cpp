#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;

Mat src;
Mat src_gray;
RNG rng(12345);

bool stack = false;
int thresh;

//Function header
void thresh_callback(int, void* );

//gb: 1.02, 1.04, 1.02
//gr: 1.04, 0.98, 1.02
void filterGreenPx(Vec3b& color) { //bgr
  if(color[1] < color[0]*1.02 || color[1] < color[2]*1.02){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterGreen(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        filterGreenPx(img.at<Vec3b>(Point(x, y)));
}

//rg: 1.3
//rb: 0
void filterRedPx(Vec3b& color) { //bgr
  if(color[2] < color[1]*1.3){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterRed(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
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
      for(int x = 0; x < img.cols; x++)
        filterBluePx(img.at<Vec3b>(Point(x, y)));
}

//rg: 0
//rb: 1.8
void filterYellowPx(Vec3b& color) { //bgr
  if(color[2] < color[0]*1.8){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterYellow(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        filterYellowPx(img.at<Vec3b>(Point(x, y)));
}

void filterStackPx(Vec3b& color) { //bgr
  if(color[1] < color[0]*1.09 || color[1] < color[2]*1.02){
    if (color[2] < color[1]*1.3) {  
      color[2] = 0;
      color[1] = 0;
      color[0] = 0;
    }
  }
}

void filterStack(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        filterStackPx(img.at<Vec3b>(Point(x, y)));
}

void makeRedPx(Vec3b& color) { //bgr
  if(color[2] > color[1]*1.3){
    color[2] = 255;
    color[1] = 0;
    color[0] = 0;
  }
}

void makeRed(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makeRedPx(img.at<Vec3b>(Point(x, y)));
}

void makeStackPx(Vec3b& color) { //bgr
  if(color[2] > color[1]*1.3){
    color[2] = 255;
    color[1] = 0;
    color[0] = 0;
  } else if(color[1] > color[0]*1.09 && color[1] > color[2]*1.02){
    color[2] = 0;
    color[1] = 255;
    color[0] = 0;
  } else {
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void makeStack(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makeStackPx(img.at<Vec3b>(Point(x, y)));
}

int getTopColor(Mat& img) {
  for(int y = 0; y < img.rows; y++) {
    for(int x = 0; x < img.cols; x++) { //bgr
      Vec3b& color = img.at<Vec3b>(Point(x, y));
      if (color[2] == 255 && color[1] == 0 && color[0] == 0) {
        return 1;
      } else if (color[2] == 0 && color[1] == 255 && color[0] == 0) {
        return 2;
      }
    }
  }
  return 0;    
}

/**
 * @function main
 */
int main(int, char** argv) {

  //VideoCapture cap(0);
  //assert(cap.isOpened());

  //Mat src2;
  //cap.read(src2);

  /// Load source image and convert it to gray
  Mat src2 = imread(argv[1], 1);
  int top = (int) (0.05*src2.rows), bottom = (int) (0.05*src2.rows);
  int left = (int) (0.05*src2.cols), right = (int) (0.05*src2.cols);
  //copyMakeBorder( src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0) );
  
  makeStack(src2);

  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  dilate(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  dilate(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  copyMakeBorder(src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0));

  //Convert image to gray and blur it
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  blur(src_gray, src_gray, Size(3,3));

  //Create Window
  const char* source_window = "Source";
  namedWindow(source_window, WINDOW_AUTOSIZE);
  imshow(source_window, src);

  //createTrackbar( " Canny thresh:", "Source", &thresh, 255, thresh_callback );
  thresh_callback( 0, 0 );

  if (stack) {
    cout << getTopColor(src2) << endl;
  }

  waitKey(0);
  return(0);
}

void thresh_callback(int, void*) {
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;
  vector<vector<Point> > hexagons;
  vector<Point> approx;

  //Convert image to gray and blur it
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  blur(src_gray, src_gray, Size(3,3));

  findContours(src_gray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

  /// Draw contours
  Mat drawing = Mat::zeros(src_gray.size(), CV_8UC3);
  int count = 0;
  double last_area = 0;
  Rect bounding;

  for (size_t i = 0; i < contours.size(); i++) {
    double area = sqrt(contourArea(contours[i]))*0.05;
    double ap = contourArea(contours[i])/arcLength(contours[i], false);

    //skip small particles or duplicate 
    if (20*area < 50 || ((last_area - 2) < 20*area  && 20*area < (last_area + 2)) || ap < 20) continue;

    approxPolyDP(contours[i], approx, area, true);
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    
    if (approx.size()) {
      last_area = 20*area;
      hexagons.push_back(approx);
      drawContours(drawing, hexagons, count, color, 2);
      bounding = boundingRect(approx);
      
      Point center((bounding.x + bounding.width/2), (bounding.y + bounding.height/2));
      double ba = bounding.width * bounding.height;

      //if (ba < 1000 || ba > 100000) continue;
      //bounding box
      rectangle(drawing, bounding.tl(), bounding.br(), color, 2, 8, 0);

      //center point
      circle(drawing, center, 2, color, 2, 8, 0);

      printf("Center: (%d, %d) \n", center.x, center.y);
      printf("Contour Area: %lf \n", last_area);
      printf("Bounding Box: %lf \n", ba);
      printf("Angle: %lf\n", center.x * 0.10625 - 34);
      printf("A/P: %lf\n", ap);

      stack = true;
      count++;
    }
  }
  //Show output picture in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}