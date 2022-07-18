#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

//函数实现
void face_detection_demo() {

	//文件夹路径
	string root_dir = "../";

	//读取以TensorFlow框架格式存储的网络模型
	dnn::Net net = dnn::readNetFromTensorflow(root_dir + "opencv_face_detector_uint8.pb", root_dir + "opencv_face_detector.pbtxt");

	//对摄像头进行人脸检测
	// VideoCapture cap("../01.mp4");
	VideoCapture cap(0);
	Mat frame;
	while (true) 
	{

		cap.read(frame);//frame为输出，read是将捕获到的视频一帧一帧的传入frame
		if (frame.empty()) 
		{
			break;
		}

		flip(frame, frame, 1);//左右翻转

		//准备深度学习模型需要的数据 （blob-斑点）
		Mat blob = dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);

		//完成推理
		Mat probs = net.forward();

		Mat detectionMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());

		//解析结果
		for (int i = 0; i < detectionMat.rows; i++) 
		{
			float confidence = detectionMat.at<float>(i, 2);//第三个值 得分
			if (confidence > 0.5) 
			{
				//因为预测来的值为[0,1]范围的数，我们还需要*原图像的宽度和长度
				int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frame.cols);
				int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frame.rows);
				int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frame.cols);
				int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frame.rows);

				Rect rect(x1, y1, x2 - x1, y2 - y1);
				rectangle(frame, rect, Scalar(0, 0, 255), 2, 8, 0);
			}
		}

		imshow("人脸检测",frame);

		int c = waitKey(1);
		if (c == 27) 
		{
			break;
		}
	}
	cap.release();
}


int main(int argc, char** argv) 
{
	face_detection_demo();
	return 0;
}
