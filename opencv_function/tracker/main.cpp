#include <opencv2/opencv.hpp>
#include <opencv2/video.hpp>
#include <opencv2/tracking.hpp>
#include <sys/time.h>
#include <opencv2/tracking/tracking_legacy.hpp>

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
Rect2d bbox = {0, 0, 0, 0};

int main(int argc, char *argv[])
{
    bool is_tracking = 0;
    string run_mode = argv[1];
    string test_data_path = argv[2];
    cout << "run_mode: " << run_mode << endl;
    cout << "test_data_path: " << test_data_path << endl;

    //使用Tracker跟踪
    Ptr<cv::legacy::Tracker> tracker;
    if(run_mode == "MIL")
    {
        tracker = cv::legacy::TrackerMIL::create();
    }
    else if (run_mode == "TLD")
    {
        tracker = cv::legacy::TrackerTLD::create();
    }
    else if (run_mode == "KCF")
    {
        tracker = cv::legacy::TrackerKCF::create();
    }
    else if (run_mode == "MedianFlow")
    {
        tracker = cv::legacy::TrackerMedianFlow::create();
    }
    else if (run_mode == "Boosting")
    {
        tracker = cv::legacy::TrackerBoosting::create();
    }
    else if (run_mode == "GOTURN")
    {
        // auto tracker = TrackerGOTURN::create(); // not bring up
    }
    else if (run_mode == "MOSSE")
    {
        tracker = cv::legacy::TrackerMOSSE::create();
    }
    else
    {}

    VideoCapture capture;
    Mat frame;
    frame = capture.open(test_data_path);
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

    capture.read(frame);
    tracker->init(frame, bbox);

    namedWindow("output", WINDOW_AUTOSIZE);
    while (capture.read(frame))
    {
        // Start timer
        int64_t time_beg = get_time_interval();
        
        is_tracking = tracker->update(frame, bbox);

        // Calculate Frames per second (FPS)
        int64_t time_end = get_time_interval();
        int64_t time_cost = time_end - time_beg;
        float fps = getTickFrequency() / (float)time_cost;

        rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
        // cout << bbox << endl;
        // Display tracker type on frame
        putText(frame, "tk algorithm: " + run_mode , \
                Point(0, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 200), 1);
        putText(frame, "time cost: " + to_string(time_cost) + " ms" , \
                Point(0, 40), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 200), 1);
        string status_str;
        if(is_tracking)
        {
            status_str = "tracking";
        }
        else
        {
            status_str = "lost";
        }
        putText(frame, "status: " + status_str, \
                 Point(0, 60), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 200), 1);

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

        cout << "select box: " << bbox.x << ", "
        << bbox.y << ", "
        << bbox.width << ", "
        << bbox.height << endl;
    }
    else if (event == EVENT_RBUTTONUP)
    {
        destroyWindow("output");
    }
    else
    {}
}


