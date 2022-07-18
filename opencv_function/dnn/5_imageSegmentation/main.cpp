#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const size_t width = 300;
const size_t height = 300;
String labelFile = "../pascal-classes.txt";
String modelFile = "../fcn8s-heavy-pascal.caffemodel";
String model_text_file = "../fcn8s-heavy-pascal.prototxt";

vector<Vec3b> readColors();
int main(int argc, char** argv) {
	Mat frame = imread("../rgb.jpg");
	if (frame.empty()) {
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("input image", cv::WINDOW_AUTOSIZE);
	imshow("input image", frame);
	resize(frame, frame, Size(500, 500));//�ı�ߴ�
	vector<Vec3b> colors = readColors();
//
	// init net  ��ʼ������
	Net net = readNetFromCaffe(model_text_file, modelFile);
	Mat blobImage = blobFromImage(frame);

	// use net   ʹ������
	float time = getTickCount();
	net.setInput(blobImage, "data");
	Mat score = net.forward("score");
	float tt = getTickCount() - time;
	printf("time consume: %.2f ms \n", (tt / getTickFrequency()) * 1000);
	
	// segmentation and display   �ָ��ʾ
	const int rows = score.size[2];
	const int cols = score.size[3];
	const int chns = score.size[1];
	Mat maxCl(rows, cols, CV_8UC1);
	Mat maxVal(rows, cols, CV_32FC1);

	// setup LUT  LUT����
	for (int c = 0; c < chns; c++) {
		for (int row = 0; row < rows; row++) {
			const float *ptrScore = score.ptr<float>(0, c, row);
			uchar *ptrMaxCl = maxCl.ptr<uchar>(row);
			float *ptrMaxVal = maxVal.ptr<float>(row);
			for (int col = 0; col < cols; col++) {
				if(ptrScore[col] > ptrMaxVal[col]) {
					ptrMaxVal[col] = ptrScore[col];
					ptrMaxCl[col] = (uchar)c;
				}
			}
		}
	}

	// look up colors �ҵ���Ӧ��ɫ
	Mat result = Mat::zeros(rows, cols, CV_8UC3);
	for (int row = 0; row < rows; row++) {
		const uchar *ptrMaxCl = maxCl.ptr<uchar>(row);
		Vec3b *ptrColor = result.ptr<Vec3b>(row);
		for (int col = 0; col < cols; col++) {
			ptrColor[col] = colors[ptrMaxCl[col]];
		}
	}
	Mat dst;
	imshow("FCN-demo1", result);
	addWeighted(frame, 0.3, result, 0.7, 0, dst);//���ӿ���
	imshow("FCN-demo", dst);

	waitKey(0);
	return 0;
}

vector<Vec3b> readColors() {
	vector<Vec3b> colors;
	ifstream fp(labelFile);
	if (!fp.is_open()) {
		printf("could not open the file...\n");
		exit(-1);
	}
	string line;
	while (!fp.eof()) {
		getline(fp, line);
		if (line.length()) {
			stringstream ss(line);
			string name;
			ss >> name;
			int temp;
			Vec3b color;
			ss >> temp;
			color[0] = (uchar)temp;
			ss >> temp;
			color[1] = (uchar)temp;
			ss >> temp;
			color[2] = (uchar)temp;
			colors.push_back(color);
		}
	}
	return colors;
}