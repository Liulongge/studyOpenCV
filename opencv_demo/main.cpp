// cmake .
// make

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, const char * argv[]) {
    string path = "../1.jpg";

    Mat image;
    image = imread( path, 1 );


    cv::imwrite("demo.jpg", image);
    // imshow( "Display Image", image );
    // waitKey(0);

    return 0;
}


