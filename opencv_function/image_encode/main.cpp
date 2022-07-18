#include <iostream>
#include <opencv2/opencv.hpp>
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

double getPSNR(Mat& src1, Mat& src2, int bb=0)
{
	int i, j;
	double sse, mse, psnr;
	sse = 0.0;
	Mat s1, s2;
	cvtColor(src1, s1, CV_BGR2GRAY);
	cvtColor(src2, s2, CV_BGR2GRAY);
	int count = 0;
	for (j = bb; j < s1.rows - bb; j++)
	{
		uchar* d = s1.ptr(j);
		uchar* s = s2.ptr(j);
		for (i = bb; i < s1.cols - bb; i++)
		{
			sse += ((d[i] - s[i]) * (d[i] - s[i]));
			count++;
		}
	}
	if (sse == 0.0 || count == 0)
	{
		return 0;
	}
	else
	{
		mse = sse / (double)(count);
		psnr = 10.0 * log10((255 * 255) / mse);
		return psnr;
	}
}
 
int main(int argc, char* argv) 
{
	Mat src = imread("../cat.jpg"); // 读入一张图片
	vector<uchar> buff; // 编码后的缓存
	vector<int> param = vector<int>(2);
	param[0] = CV_IMWRITE_JPEG_QUALITY; // 写质量
	param[1] = 10; // default(95) 0-100 // 数值越大，质量越好

    int64_t beg_time = get_time_interval();
    for(int i = 0; i < 100; i++)
    {
        imencode(".jpg", src, buff, param);
    }
    int64_t end_time = get_time_interval();
    cout << "encode cast time: " << end_time - beg_time << endl;

    Mat jpegimage = imdecode(Mat(buff), CV_LOAD_IMAGE_COLOR);
    double psnr = getPSNR(src, jpegimage); // get PSNR
    cout << "psnr: " <<  psnr << endl;
    imwrite("encode.jpg", jpegimage);
	return 0;
}