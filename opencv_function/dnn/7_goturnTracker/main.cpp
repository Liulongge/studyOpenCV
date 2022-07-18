#include <opencv2/tracking.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
 
using namespace std;
using namespace cv;
 
int main(int argc, char** argv) 
{
	// VideoCapture cap(0);
	VideoCapture cap("../2.mp4");
	if (!cap.isOpened())
	{
		cout << "***Could not initialize capturing...***\n";
		return -1;
	}

	TrackerGOTURN::Params param;
	param.modelBin = "../goturn.caffemodel";
	param.modelTxt = "../goturn.prototxt";
	auto tracker = TrackerGOTURN::create(param);
 
	if (!tracker)
	{
		cout << "***Error in the instantiation of the tracker...***\n";
		return -1;
	}
 
	Mat frame;
	namedWindow("Tracking API", 1);
	Mat image;
	Rect2i boundingBox;
	bool paused = false;
 
	cap >> frame;
	cout << frame.type() << " " << frame.channels() << " ";
	frame.copyTo(image);
	imshow("Tracking API", image);
	waitKey(1);
	boundingBox = selectROI("Tracking API", image, false, false);
	bool initialized = false;
	int frameCounter = 0;
	int64 timeTotal = 0;
 
	for (;; )
	{
		if (!paused)
		{
			if (initialized) 
			{
				cap >> frame;
				if (frame.empty()) {
					break;
				}
				frame.copyTo(image);
			}
			// flip(image, image, 1);//左右翻转
			if (!initialized)
			{
				//initializes the tracker
				tracker->init(frame, boundingBox);
				initialized = true;
			}
			else if (initialized)
			{
				int64 frameTime = getTickCount();
				//updates the tracker
				tracker->update(frame, boundingBox);
				frameTime = getTickCount() - frameTime;
				timeTotal += frameTime;
			}
			rectangle(image, boundingBox, Scalar(255, 0, 0), 2, 1);
			imshow("Tracking API", image);
			frameCounter++;
		}
 
		char c = (char)waitKey(1);
		if (c == 'q')
			break;
		if (c == 'p')
			paused = !paused;
	}
 
	double s = frameCounter / (timeTotal / getTickFrequency());
	printf("FPS: %f\n", s);
	getchar();
	return 0;
}