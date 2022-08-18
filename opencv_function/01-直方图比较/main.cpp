#define INPUT_TITLE0 "input image src"
#define INPUT_TITLE1 "input image srctest1"
#define INPUT_TITLE2 "input image srctest2"
#define OUTPUT_TITLE "name"
 
#include<iostream>
#include<math.h>
#include<opencv2/opencv.hpp>
 
using namespace std;
using namespace cv;
 
string convertToString(double d);
 
int main() {
	// 加载图像 
	Mat src, srctest1, srctest2;
	src = imread("../cat_1.jpg");
	srctest1 = imread("../cat_2.jpg");
	srctest2 = imread("../cat_4.jpg");
	
	if (!src.data|| !srctest1.data|| !srctest2.data)
	{
		cout << "ERROR : could not load image.";
		return -1;
	}
	
	imshow("【src 原图】", src);
	imshow("【srctest1 原图】", srctest1);
	imshow("【srctest2 原图】", srctest2);
 
	//从RGB色彩空间转化为HSV色彩空间
	cvtColor(src, src, COLOR_BGR2HSV);
	cvtColor(srctest1, srctest1, COLOR_BGR2HSV);
	cvtColor(srctest2, srctest2, COLOR_BGR2HSV);
 
	//定义直方图计算所需要的各种参数
	int h_bins = 50;
	int s_bins = 60;
	int histSize[] = { h_bins,s_bins };
 
	float h_ranges[] = { 0,180 };
	float s_ranges[] = { 0,255 };
	const float* ranges[] = { h_ranges, s_ranges };
 
	int channels[] = { 0,1 };
 
	//MatND 是 Mat的别名，方便区分经过直方图计算处理后和输入图像
	MatND hist_src;
	MatND hist_srctest1;
	MatND hist_srctest2;
 
	//计算直方图并归一化处理
	calcHist(&src, 1, channels, Mat(), hist_src, 2, histSize, ranges, true, false);
	normalize(hist_src, hist_src, 0, 1, NORM_MINMAX, -1, Mat());
 
	calcHist(&srctest1, 1, channels, Mat(), hist_srctest1, 2, histSize, ranges, true, false);
	normalize(hist_srctest1, hist_srctest1, 0, 1, NORM_MINMAX, -1, Mat());
 
	calcHist(&srctest2, 1, channels, Mat(), hist_srctest2, 2, histSize, ranges, true, false);
	normalize(hist_srctest2, hist_srctest2, 0, 1, NORM_MINMAX, -1, Mat());
 
	//直方图比较
	double src_src = compareHist(hist_src, hist_src, HISTCMP_CHISQR);
	double src_srctest1 = compareHist(hist_src, hist_srctest1, HISTCMP_CHISQR);
	double src_srctest2 = compareHist(hist_src, hist_srctest2, HISTCMP_CHISQR);
	double srctest1_srctest2 = compareHist(hist_srctest1, hist_srctest2, HISTCMP_CHISQR);
 
	cout << "src compare with src correlation value : " << src_src << endl;
	cout << "src compare with srctest1 correlation value : " << src_srctest1 << endl;
	cout << "src compare with srctest2 correlation value : " << src_srctest2 << endl;
 
	//给每个图像上添加文字，内容为该图片和原始图片的比较结果
	putText(src, convertToString(src_src), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 255, 255), 2, LINE_AA);
	putText(srctest1, convertToString(src_srctest1), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(0, 0, 255), 2, LINE_AA);
	putText(srctest2, convertToString(src_srctest2), Point(50, 50), FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 255), 2, LINE_AA);
 
	//图像的显示
	namedWindow(INPUT_TITLE0, WINDOW_AUTOSIZE);
	namedWindow(INPUT_TITLE1, WINDOW_AUTOSIZE);
	namedWindow(INPUT_TITLE2, WINDOW_AUTOSIZE);
	//namedWindow(OUTPUT_TITLE, CV_WINDOW_AUTOSIZE);
 
	imshow(INPUT_TITLE0, src);
	imshow(INPUT_TITLE1, srctest1);
	imshow(INPUT_TITLE2, srctest2);
	
 
	waitKey(0);
	return 0;
}
 
string convertToString(double d) {
	ostringstream os;
	if (os<<d)
	{
		return os.str();
	}
	return "invalid conversion";
}