// cmake .
// make

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

using namespace cv;
using namespace std;
int main(int argc, const char * argv[]) 
{
    string path = "../1.jpg";

    Mat src_image = imread(path);
    uint32_t image_size = src_image.cols * src_image.rows * src_image.channels();

    // 1.resize
    uint16_t dst_hight = src_image.rows / 2; // 用于描述外部输入的图像size
    uint16_t dst_width = src_image.cols / 2;
    uint16_t dst_channel = 3;
    uint8_t *origin_buffer = (uint8_t *)malloc(dst_hight * dst_width * dst_channel * sizeof(uint8_t));  // 用于模拟外部输的图像内存空间

    Mat resize_image(src_image.rows, src_image.cols, CV_8UC3, origin_buffer);  // 使用已有内存空间定义mat数据类型，使resize操作结果直接写入外部内存
    resize(src_image, resize_image, Size(dst_width, dst_hight), INTER_NEAREST); // INTER_NEAREST 速度最快
    cv::imwrite("resize_image.jpg", resize_image);

    // 2.归一化
    float *float_buffer = (float *)malloc(dst_hight * dst_width * dst_channel * sizeof(float));  // 用于模拟外部输的图像内存空间
    uint8_t mean = 128;
    uint8_t std = 128;
    Mat float_image(dst_hight, dst_width, CV_32FC3, float_buffer);
    resize_image.convertTo(float_image, CV_32FC3);
    float_image = (float_image - mean) / std; // 归一化 -1 ~ 1，Mat数据类型支持与标量的运算

    // 还原回去，便于显示
    uint8_t *display_buffer = (uint8_t *)malloc(dst_hight * dst_width * dst_channel * sizeof(uint8_t));
    Mat display_image(dst_hight, dst_width, CV_8UC3, display_buffer);
    for(int i = 0; i < dst_hight * dst_width * dst_channel * sizeof(uint8_t); i++)
    {
        display_buffer[i] = (uint8_t)(float_buffer[i] * std + mean);
    }
    cv::imwrite("float_diaplay_image.jpg", display_image);

    free(origin_buffer);
    free(float_buffer);
    free(display_buffer);
    return 0;
}


