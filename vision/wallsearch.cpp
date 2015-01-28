//THIS IS ONLY USED TO FIND CUBES
//USE WALLSEARCH TO FIND WALLS
//ALL OF THESE FUNCTIONS APPLY TO STACKS ONLY
//IGNORE THE WALLS AND PLATFORMS HERE

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "wallsearch.h"

using namespace cv;

//br: 1.2, 1.5?
//bg: 1.2
void WallSearch::filterBluePx(Vec3b& color) { //bgr
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

void WallSearch::filterBlue(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        filterBluePx(img.at<Vec3b>(Point(x, y)));
}

void WallSearch::makeBluePx(Vec3b& color) { //bgr
  if(color[0] > color[1]*1.2 && color[0] > color[2]*1.2){
    color[2] = 0;
    color[1] = 0;
    color[0] = 255;
  }
}

void WallSearch::makeBlue(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makeBluePx(img.at<Vec3b>(Point(x, y)));
}

void WallSearch::makeYellowPx(Vec3b& color) {//bgr
  if(color[2] > color[0]*1.8){
    color[2] = 255;
    color[1] = 255;
    color[0] = 0;
  }
}

void WallSearch::makeYellow(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeYellowPx(img.at<Vec3b>(Point(x, y)));
}

void WallSearch::makeWallsPx(Vec3b& color) { //bgr
  if (color[2] > color[0]*1.8) {
    color[2] = 255;
    color[1] = 255;
    color[0] = 0;
  } else if (color[0] > color[1]*1.2 && color[0] > color[2]*1.2) {
    color[2] = 0;
    color[1] = 0;
    color[0] = 255;
  } else {
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void WallSearch::makeWalls(Mat& img) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makeWallsPx(img.at<Vec3b>(Point(x, y)));
}

int WallSearch::getTopColor(Mat& img) {
  for(int y = 0; y < img.rows; y++) {
    for(int x = 0; x < img.cols; x++) { //bgr
      Vec3b& color = img.at<Vec3b>(Point(x, y));
      if (color[2] == 255 && color[1] == 0 && color[0] == 0) { //red
        return 1;
      } else if (color[2] == 0 && color[1] == 255 && color[0] == 0) { //green
        return 2;
      } else if (color[2] == 0 && color[1] == 0 && color[0] == 255) { //blue
        return 3;
      } else if (color[2] == 255 && color[1] == 255 && color[0] == 0) { //yellow
        return 4;
      }
    }
  }
  return 0;
}

void WallSearch::processImage(Mat& src2) {
  centerXs.clear();
  centerYs.clear();
  angles.clear();

  wall = false;

  int top = (int) (0.05*src2.rows), bottom = (int) (0.05*src2.rows);
  int left = (int) (0.05*src2.cols), right = (int) (0.05*src2.cols);
  
  findWalls(src2);

  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  dilate(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  dilate(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
  erode(src2, src2, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

  copyMakeBorder(src2, src, top, bottom, left, right, BORDER_CONSTANT, Scalar(0,0,0));

  //Convert image to gray and blur it
  cvtColor(src, src_gray, COLOR_BGR2GRAY);
  blur(src_gray, src_gray, Size(3,3));

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
    if (20*area < 50 || ((last_area - 2) < 20*area  && 20*area < (last_area + 2))) continue;

    approxPolyDP(contours[i], approx, area, true);
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    
    if (approx.size()) {
      last_area = 20*area;
      hexagons.push_back(approx);
      drawContours(drawing, hexagons, count, color, 2);
      bounding = boundingRect(approx);
      
      Point center((bounding.x + bounding.width/2), (bounding.y + bounding.height/2));
      centerXs.push_back(center.x);
      centerYs.push_back(center.y);

      double ba = bounding.width * bounding.height;

      //bounding box
      rectangle(drawing, bounding.tl(), bounding.br(), color, 2, 8, 0);

      //center point
      circle(drawing, center, 2, color, 2, 8, 0);

      printf("Center: (%d, %d) \n", center.x, center.y);
      printf("Contour Area: %lf \n", last_area);
      printf("Bounding Box: %lf \n", ba);

      wall = true;
      count++;
    }
  }
}

bool WallSearch::findWall(Mat& img) {
  //processImage(img)
  return wall;
}

vector<int> WallSearch::getCenterX(Mat& img) {
  //processImage(img);
  return centerXs;
}

vector<int> WallSearch::getCenterY(Mat& img) {
  //processImage(img);
  return centerYs;
}