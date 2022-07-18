#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <sys/time.h>

using namespace std;
using namespace cv;

static int64_t get_time_interval(void)
{
	struct timeval t_curr;
    const static timeval t_start = {0};
	gettimeofday(&t_curr, NULL);
	return  (t_curr.tv_sec * 1000) + (t_curr.tv_usec / 1000) - ((t_start.tv_sec * 1000) + (t_start.tv_usec / 1000));
}

#include "pch.h"
#include "Mosse.h"
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
using namespace cuda;

int main()
{
	cv::Rect ROI;
	//std::vector<cv::Rect> boundingBOX;
	cv::Rect boundingBOX;
	cv::Mat frame;
	MOSSETracker mossetracker;
	cv::VideoCapture cap("../man.mp4");
	cap >> frame;
	//resize(frame, frame, cv::Size(800, 600));
	ROI = selectROI(frame);
	mossetracker.initTracker(frame,ROI);
	while (cap.read(frame))
	{
        int64_t time_beg = get_time_interval();
		mossetracker.updateTracker(frame, boundingBOX, 0.5);
        int64_t time_end = get_time_interval();
        int64_t time_cost = time_end - time_beg;
        putText(frame, "time cost: " + to_string(time_cost) + " ms" , \
                Point(0, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 200), 1);
		rectangle(frame, boundingBOX, cv::Scalar(0, 0, 0), 5);
		cv::imshow("frame", frame);
		if (waitKey(1) == 27) break;
	}
	return 0;
}
