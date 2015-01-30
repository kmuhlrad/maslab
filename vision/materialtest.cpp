////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

void filterGreenPx(Vec3b& color, double& gb, double& gr) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[1] < color[0]*gb || color[1] < color[2]*gr){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterGreen(Mat& img, double& gb, double& gr) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterGreenPx(img.at<Vec3b>(Point(x, y)), gb, gr);
}

void filterRedPx(Vec3b& color, double& rb, double& rg) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[2] < color[0]*rb || color[2] < color[1]*rg){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterRed(Mat& img, double& rb, double& rg) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterRedPx(img.at<Vec3b>(Point(x, y)), rb, rg);
}

void filterBluePx(Vec3b& color, double& bg, double& br) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[0] < color[1]*bg || color[0] < color[2]*br){
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void filterBlue(Mat& img, double& bg, double& br) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        filterBluePx(img.at<Vec3b>(Point(x, y)), bg, br);
}

//OPPOSITE OF FILTERING
void makeGreenPx(Vec3b& color, double& gb, double& gr) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[1] > color[0]*gb && color[1] > color[2]*gr){
    color[2] = 0;
    color[1] = 255;
    color[0] = 0;
  }
}

void makeGreen(Mat& img, double& gb, double& gr) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeGreenPx(img.at<Vec3b>(Point(x, y)), gb, gr);
}

void makeRedPx(Vec3b& color, double& rb, double& rg) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[2] > color[0]*rb && color[2] > color[1]*rg){
    color[2] = 255;
    color[1] = 0;
    color[0] = 0;
  }
}

void makeRed(Mat& img, double& rb, double& rg) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeRedPx(img.at<Vec3b>(Point(x, y)), rb, rg);
}

void makeBluePx(Vec3b& color, double& bg, double& br) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[0] > color[1]*bg || color[0] > color[2]*br){
    color[2] = 0;
    color[1] = 0;
    color[0] = 255;
  }
}

void makeBlue(Mat& img, double& bg, double& br) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeBluePx(img.at<Vec3b>(Point(x, y)), bg, br);
}

void makeStackPx(Vec3b& color, double& rb, double& rg, double& gb, double& gr) {//bgr
//        vector<vector<bool> > eliminate(,vector<bool>());
  if(color[2] > color[0]*rb && color[2] > color[1]*rg){
    color[2] = 255;
    color[1] = 0;
    color[0] = 0;
  } else if(color[1] > color[0]*gb && color[1] > color[2]*gr){
    color[2] = 0;
    color[1] = 255;
    color[0] = 0;
  }
}

void makeStack(Mat& img, double& rb, double& rg, double& gb, double& gr) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++) //bgr
        makeStackPx(img.at<Vec3b>(Point(x, y)), rb, rg, gb, gr);
}

void makePlatformPx(Vec3b& color, double& rb, double& rg, double& hrg) { //bgr
  if(color[2] > color[0]*rb && color[2] > color[1]*rg && color[2] < color[1]*hrg){
    color[2] = 255;
    color[1] = 255;
    color[0] = 0;
  } else {
    color[2] = 0;
    color[1] = 0;
    color[0] = 0;
  }
}

void makePlatform(Mat& img, double& rb, double& rg, double& hrg) {
   for(int y = 0; y < img.rows; y++)
      for(int x = 0; x < img.cols; x++)
        makePlatformPx(img.at<Vec3b>(Point(x, y)), rb, rg, hrg);
}

int main(int, char** argv) {
  Mat img = imread(argv[1], 1); 

  int gb=0;
  int gr=0;

  int rb=0;
  int rg=0;

  int bg=0;
  int br=0;

  int des=9;
  int hrg=0;

  //create a window called "Control"
  namedWindow("Control", CV_WINDOW_NORMAL);

  //Create trackbars in "Control" window

  /*
  //green
  createTrackbar("G/B minimum*100", "Control", &gb, 300);
  createTrackbar("G/R minimum*100", "Control", &gr, 300);
  */


  //red
  createTrackbar("R/B minimum*100", "Control", &rb, 300);
  createTrackbar("R/Gminimum*100", "Control", &rg, 300);
  createTrackbar("R/Gmax*100", "Control", &hrg, 300);

  /*
  //blue
  createTrackbar("B/G minimum*100", "Control", &bg, 300);
  createTrackbar("B/R minimum*100", "Control", &br, 300);
  */

  //createTrackbar("Dilate/Erode Size", "Control", &des, 50);

  while (true) {
    Mat imgThresholded;
    img.copyTo(imgThresholded);

    /*
    //green
    double dgb = ((double)gb)/100, dgr = ((double)gr)/100;
    makeGreen(imgThresholded, dgb, dgr);
    cout << "gb: " << dgb << " \t gr: " << dgr << endl;
    */

    
    //red
    double drb = ((double)rb)/100, drg = ((double)rg)/100, dhrg = ((double)hrg)/100;
    makePlatform(imgThresholded, drb, drg, dhrg);
    cout << "rb: " << drb << " \t rg: " << drg << " \t hrg: " << dhrg << endl;
    

    /*
    //blue
    double dbg = ((double)bg)/100, dbr = ((double)br)/100;
    filterBlue(imgThresholded, dbg, dbr);
    cout << "bg: " << dbg << " \t br: " << dbr << endl;
    */

    /*
    //stack
    double drb = ((double)rb)/100, drg = ((double)rg)/100;
    double dgb = ((double)gb)/100, dgr = ((double)gr)/100;
    makeStack(imgThresholded, drb, drg);
    cout << "rb: " << drb << " \t rg: " << drg << "\t gb: " << dgb << " \t gr: " << dgr << endl;
    */

    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(9, 9)));

    //morphological closing (removes small holes from the foreground)
    dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(des, des)));
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(des, des)));
    

    //morphological opening (removes small objects from the foreground)
    /* 
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

    //morphological closing (removes small holes from the foreground)
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

    //Calculate the moments of the thresholded image
    Moments oMoments = moments(imgThresholded);

    double dM01 = oMoments.m01;
    double dM10 = oMoments.m10;
    double dArea = oMoments.m00;

    //if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
    if (dArea > 10000) {
      //calculate the position of the ball
      int posX = dM10 / dArea;
      int posY = dM01 / dArea;        
        
      if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0) {
        //Draw a red line from the previous point to the current point
        line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
      }

      iLastX = posX;
      iLastY = posY;
    }*/

    //imshow("Thresholded Image", imgThresholded); //show the thresholded image

    imshow("Filtered", imgThresholded); //show the original image
    imshow("Original", img); //show the original image
    
    //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
    if (waitKey(30) == 27) {
      cout << "esc key is pressed by user" << endl;
      break; 
    }
  }

  return 0;
}
