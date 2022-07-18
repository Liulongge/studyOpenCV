#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/video/tracking.hpp>
#include <sys/time.h>
#include "tracker.h"
#include <assert.h>
// #include "selectROI.h"

using namespace std;
using namespace cv;

static int64_t get_time_interval(void)
{
	struct timeval t_curr;
    const static timeval t_start = {0};
	gettimeofday(&t_curr, NULL);
	return  (t_curr.tv_sec * 1000) + (t_curr.tv_usec / 1000) - ((t_start.tv_sec * 1000) + (t_start.tv_usec / 1000));
}

void draw_rectangle(int event, int x, int y, int flags, void*);
Mat firstFrame;
Point previousPoint, currentPoint;
Rect bbox = {300, 8, 294, 292};

int main(int argc, char *argv[])
{
    VideoCapture capture;
    Mat frame;
    frame = capture.open("../man.mp4");
    if(!capture.isOpened())
    {
        printf("can not open ...\n");
        return -1;
    }
    //获取视频的第一帧,并框选目标
    capture.read(firstFrame);
    if(!firstFrame.empty())
    {
        namedWindow("output", WINDOW_AUTOSIZE);
        putText(firstFrame, "please select one box by mouse",
                Point(0, 20), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 200), 1);
        putText(firstFrame, "then press any key to start tracking.",
                Point(0, 40), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 200), 1);
        imshow("output", firstFrame);
        setMouseCallback("output", draw_rectangle, 0);
        waitKey(0);
    }

    //使用TrackerMIL跟踪
    // Ptr<TrackerMIL> tracker= TrackerMIL::create();
    // Ptr<TrackerTLD> tracker= TrackerTLD::create();
    // Ptr<TrackerKCF> tracker = TrackerKCF::create();
    // Ptr<TrackerMedianFlow> tracker = TrackerMedianFlow::create();
    // Ptr<TrackerBoosting> tracker= TrackerBoosting::create();
    // Ptr<TrackerGOTURN> tracker = TrackerGOTURN::create();
    // Ptr<TrackerMOSSE> tracker = TrackerMOSSE::create();

    mosseTracker track;

    capture.read(frame);
    // tracker->init(frame, bbox);
    track.init(bbox, frame);

    namedWindow("output", WINDOW_AUTOSIZE);
    while (capture.read(frame))
    {
        // Start timer
        int64_t time_beg = get_time_interval();
        
        // tracker->update(frame, bbox);
        bbox = track.update(frame);

        // Calculate Frames per second (FPS)
        int64_t time_end = get_time_interval();
        int64_t time_cost = time_end - time_beg;
        float fps = getTickFrequency() / (float)time_cost;

        rectangle(frame,bbox, Scalar(255, 0, 0), 2, 1);
        // Display tracker type on frame
        putText(frame, "time cost: " + to_string(time_cost) + " ms" , \
                Point(0, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 200), 1);

        imshow("output", frame);
        if(waitKey(20)=='q')
        return 0;
    }
    capture.release();
    destroyWindow("output");
    return 0;
}

//框选目标
void draw_rectangle(int event, int x, int y, int flags, void*)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        previousPoint = Point(x, y);

    }
    else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))
    {
        Mat tmp;
        firstFrame.copyTo(tmp);
        currentPoint = Point(x, y);
        rectangle(tmp, previousPoint, currentPoint, Scalar(255, 0, 0), 1, 8, 0);
        imshow("output", tmp);
    }
    else if (event == EVENT_LBUTTONUP)
    {
        bbox.x = previousPoint.x;
        bbox.y = previousPoint.y;
        bbox.width = abs(previousPoint.x-currentPoint.x);
        bbox.height = abs(previousPoint.y-currentPoint.y);

        cout << "select box: " << bbox.x << bbox.y << bbox.width << bbox.height << endl;
    }
    else if (event == EVENT_RBUTTONUP)
    {
        destroyWindow("output");
    }
    else
    {}
}


