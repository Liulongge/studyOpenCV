#include "tracker.h"
#include <assert.h>
#include "selectROI.h"
using namespace std;
using namespace cv;

int run()
{
	mosseTracker track;
	SelectROI box;
	box.init_param();
	bool init = true;
	cv::Rect roi;
	std::string trackingWindow = "tracking.jpg";

	VideoCapture capture;
    Mat frame;
	string test_data_path = "../woman.mp4";
    frame = capture.open(test_data_path);
    if(!capture.isOpened())
    {
        printf("can not open ...\n");
        return -1;
    }

	while(capture.read(frame))
	{
		if(init)
		{
			roi = box.add(trackingWindow, frame);
			track.init(roi, frame);
			init = false;
		}
		else 
			roi = track.update(frame);
		cv::rectangle(frame, roi, cv::Scalar(255,255,0));
		cv::imshow(trackingWindow, frame);
		cv::waitKey(20);
	}
	capture.release();
	box.exit();
	return 0;
}


int main()
{
	run();
	return 0;
}