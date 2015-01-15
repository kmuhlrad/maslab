

#include "opencv2/opencv.hpp"

using namespace cv;

int main(int, char**)
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    Mat CIE;
//    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, CV_BGR2HSV);
        cvtColor(frame, CIE, CV_BGR2Lab);
//        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
//        Canny(edges, edges, 0, 30, 3);
        imshow("hsv", edges);
        imshow("bgr", frame);
        imshow("cie", CIE);
        if(waitKey(30) == 'q') break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}


