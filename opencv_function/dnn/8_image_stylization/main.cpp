// This script is used to run style transfer models from '
// https://github.com/jcjohnson/fast-neural-style using OpenCV

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;


int main(int argc, char **argv)
{
	// candy.t7
	// composition_vii.t7
	// feathers.t7
	// la_muse.t7
	// mosaic.t7
	// starry_night.t7
	// the_scream.t7
	// the_wave.t7
	// udnie.t7
	string modelBin = "../udnie.t7";
	string imageFile = "../cat.jpg";

	float scale = 1.0;
	cv::Scalar mean { 103.939, 116.779, 123.68 };
	bool swapRB = false;
	bool crop = false;
	bool useOpenCL = false;

	// VideoCapture cap;
	// cap.open(0);

	Mat img;
	img = imread(imageFile);
	if (img.empty()) {
		cout << "Can't read image from file: " << imageFile << endl;
		return 2;
	}

	// Load model
	Net net = dnn::readNetFromTorch(modelBin);
	if (useOpenCL)
		net.setPreferableTarget(DNN_TARGET_OPENCL);

	// while (cap.read(img)) 
	{
		// Create a 4D blob from a frame.
		Mat inputBlob = blobFromImage(img,scale, img.size(),mean,swapRB,crop);

		// forward netword
		net.setInput(inputBlob);
		Mat output = net.forward();
		
		// process output
		Mat(output.size[2], output.size[3], CV_32F, output.ptr<float>(0, 0)) += 103.939;
		Mat(output.size[2], output.size[3], CV_32F, output.ptr<float>(0, 1)) += 116.779;
		Mat(output.size[2], output.size[3], CV_32F, output.ptr<float>(0, 2)) += 123.68;

		std::vector<cv::Mat> ress;
		imagesFromBlob(output, ress);


		// show res
		Mat res;
		ress[0].convertTo(res, CV_8UC3);
		imshow("origin", img);
		imshow("reslut", res);

		// char c = waitKey(1);
		// if (c == 27) 
		// {
		// 	break;
		// }
	}
	

	waitKey();
	return 0;
}

