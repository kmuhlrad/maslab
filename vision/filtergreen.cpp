#include "opencv2/core/core_c.h"
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "vector"
using namespace cv;

/*void filterRed(Vec3b& color) {
	if(color[2] < color[1]*1.7 || color[2] < color[0]*1.7){
                    color[2] = 0;
                }
else{
 color[2] = 255;
}
                color[1] = 0;
                color[0] = 0;
}*/

/*void filterRed(Vec3b& color) {
	if(color[2] < color[1]*1.7 || color[2] < color[0]*1.7){
                    color[2] = 0;
                
                color[1] = 0;
                color[0] = 0;
	}
 
}*/

void filterRed(Vec3b& color) {
        //vector<vector<bool> > eliminate(,vector<bool>());
    //0 = b, 1 = g, 2 = r?? or rgb?
	if(color[2] < color[1]*1.7 || color[2] < color[0]*1.7){
                    color[2] = 0;
                
                color[1] = 0;
                color[0] = 0;
	}
 
}

int main(int, char** argv)
{

    Mat img = imread(argv[1], 1);
    for(int y = 0; y < img.rows ; y++)
    	for(int x = 0; x < img.cols;x++)//bgr
                filterRed(img.at<Vec3b>(Point(x,y)));
    imshow("opencvtest",img);
    waitKey(0);

    return 0;
}

