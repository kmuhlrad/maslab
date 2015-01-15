////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

 int main( int argc, char** argv )
 {
    VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return -1;
    }


    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    namedWindow("LAB", CV_WINDOW_AUTOSIZE); //create a window called "Control"
  int iLowL = 0;
 int iHighL = 255;

  int iLowA = 0; 
 int iHighA = 255;

  int iLowB = 0;
 int iHighB = 255;

  //Create trackbars in "Control" window
 createTrackbar("LowL", "Control", &iLowL, 255); //Hue (0 - 179)
 createTrackbar("HighL", "Control", &iHighL, 255);

  createTrackbar("LowA", "Control", &iLowA, 255); //Saturation (0 - 255)
 createTrackbar("HighA", "Control", &iHighA, 255);

  createTrackbar("LowB", "Control", &iLowB, 255);//Value (0 - 255)
 createTrackbar("HighB", "Control", &iHighB, 255);

  int iLastX = -1; 
 int iLastY = -1;

  //Capture a temporary image from the camera
 Mat imgTmp;
 cap.read(imgTmp); 

  //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
 

    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video



         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

    Mat imgLAB;

   cvtColor(imgOriginal, imgLAB, COLOR_BGR2Lab); //Convert the captured frame from BGR to HSV
 
  Mat imgThresholded;

   inRange(imgLAB, Scalar(iLowL, iLowA, iLowB), Scalar(iHighL, iHighA, iHighB), imgThresholded); //Threshold the image
      
  //morphological opening (removes small objects from the foreground)
/*  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 

   //morphological closing (removes small holes from the foreground)
  dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
  erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

   //Calculate the moments of the thresholded image
  Moments oMoments = moments(imgThresholded);

   double dM01 = oMoments.m01;
  double dM10 = oMoments.m10;
  double dArea = oMoments.m00;

   // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero 
  if (dArea > 10000)
  {
   //calculate the position of the ball
   int posX = dM10 / dArea;
   int posY = dM01 / dArea;        
        
   if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
   {
    //Draw a red line from the previous point to the current point
    line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
   }

    iLastX = posX;
   iLastY = posY;
  }*/

   imshow("Thresholded Image", imgThresholded); //show the thresholded image

   imgOriginal = imgOriginal;// + imgLines;

  imshow("LAB", imgLAB); //show the original image
  imshow("Original", imgOriginal); //show the original image
        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
       {
            cout << "esc key is pressed by user" << endl;
            break; 
       }
    }

   return 0;
};
