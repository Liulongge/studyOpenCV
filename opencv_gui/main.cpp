#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;
#define WINDOW_NAME "鼠标响应事件"
//每次鼠标事件发生的时候，该函数都被调用。其中，event指的是鼠标事件，x和y代表
//鼠标指针在图像中的坐标，flag指EVENT_FLAG的组合，param是用户定义到SetMouseCallback
//函数调用的参数。
void on_MouseHandle(int event, int x, int y, int flag, void* param);
//画出一个彩色的矩形
void DrawRectangle(Mat& img, Rect box);
 
Rect rect;
bool drawRectangle = false;
RNG rng(12345);//传入一个64位整型参数作为随机数产生器的初值
 
int main(int argc, char** argv) 
{
	rect = Rect(-1, -1, 0, 0);
	Mat srcImg(600, 800, CV_8UC3), tempImg;
	srcImg = Scalar(0);
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImg);
	//程序主循环，当进行绘制的标识为真时，进行检测
	srcImg.copyTo(tempImg);
    while (1) 
    {
		if (drawRectangle) 
        {
            srcImg.copyTo(tempImg);
			DrawRectangle(tempImg, rect);		
		}
		imshow(WINDOW_NAME, tempImg);
		if (waitKey(10) == 27)
        {
            break;
        }	
	}
	return 0;
}
void on_MouseHandle(int event, int x, int y, int flag, void* param) 
{
	Mat& image = *(Mat*)param;
	switch (event) 
    {
	case EVENT_MOUSEMOVE: 
    {
        cout << "EVENT_MOUSEMOVE" << endl;
		if (drawRectangle) 
        {
			rect.width = x - rect.x;
			rect.height = y - rect.y;
		}
		
	}
	break;
 
	case EVENT_LBUTTONDOWN: 
    {
        cout << "EVENT_LBUTTONDOWN" << endl;
		drawRectangle = true;
		rect = Rect(x, y, 0, 0);	
	}
	break;
	case EVENT_LBUTTONUP: 
    {
        cout << "EVENT_LBUTTONUP" << endl;
		drawRectangle = false;
		if (rect.width < 0) 
        {
			rect.x += rect.width;
			rect.width *= -1;
		}
		if (rect.height < 0) 
        {
			rect.y += rect.height;
			rect.height *= -1;
		}
		DrawRectangle(image, rect);
	}
	break;
 
	}
}

void DrawRectangle(Mat& img, Rect box) 
{
	// rectangle(img, box.tl(), box.br(), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
	rectangle(img, box.tl(), box.br(), Scalar(0,0,255));
}