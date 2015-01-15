#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
 
using namespace cv;
 
int main( int argc, char** argv )
{
    Mat src, gray, dst, abs_dst;
    src = imread(argv[1]);
    if(!src.data) return -1;
 
    /// Remove noise by blurring with a Gaussian filter
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
    cvtColor( src, gray, CV_RGB2GRAY );
 
    /// Apply Laplace function
    Laplacian( gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT );
    convertScaleAbs( dst, abs_dst );
    imshow( "result", abs_dst );
 
    waitKey(0);
    return 0;
}
