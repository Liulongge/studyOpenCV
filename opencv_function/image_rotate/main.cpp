// cmake .
// make

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
#include <sys/time.h>

using namespace cv;
using namespace std;

// 从实验看，retate时间最短

// Calculate time interval between current and t_start
static int64_t get_time_interval(void)
{
	struct timeval t_curr;
    const static timeval t_start = {0};
	gettimeofday(&t_curr, NULL);
	return  (t_curr.tv_sec * 1000) + (t_curr.tv_usec / 1000) - ((t_start.tv_sec * 1000) + (t_start.tv_usec / 1000));
}

int main(int argc, const char * argv[]) 
{
    string path = "../cat.jpg";

    Mat src_image = imread(path);
    int64_t beg_time;
    int64_t end_time;
    uint16_t img_width = src_image.cols;
    uint16_t img_hight = src_image.rows;
    uint16_t img_channel = src_image.channels();
    uint32_t image_size = img_width * img_hight * src_image.channels();
    Mat src_image1 = src_image.clone();
    Mat src_image2 = src_image.clone();
    Mat src_image3 = src_image.clone();
    Mat src_image4 = src_image.clone();
    Mat src_image5 = src_image.clone();
    Mat src_image6 = src_image.clone();

    uint8_t *rotate90_buffer = (uint8_t *)malloc(img_width * img_hight * img_channel * sizeof(uint8_t));
    uint8_t *rotate180_buffer = (uint8_t *)malloc(img_width * img_hight * img_channel * sizeof(uint8_t));
    uint8_t *rotate270_buffer = (uint8_t *)malloc(img_width * img_hight * img_channel * sizeof(uint8_t));
    // 1.顺时针旋转90度
    // | 1 | 2 |      T       | 1 | 3 |    Y轴镜像     | 3 | 1 |
    // ---------   ------->   ---------   ------->    ---------
    // | 3 | 4 |              | 2 | 4 |               | 4 | 2 |
    Mat rotate90_image(img_width, img_hight, CV_8UC3, rotate90_buffer);
    beg_time = get_time_interval();
    transpose(src_image1, src_image1); 
    flip(src_image1, rotate90_image, 1);
    end_time = get_time_interval();
    printf("transpose + flip 顺时针旋转90耗时: %ld\n", end_time - beg_time);
    imwrite("rotate90_image.jpg", rotate90_image);

    // 2.旋转180度
    Mat rotate180_image(img_hight, img_width, CV_8UC3, rotate180_buffer);
    beg_time = get_time_interval();
    flip(src_image2, rotate180_image, -1);
    end_time = get_time_interval();
    printf("flip 顺时针旋转180耗时: %ld\n", end_time - beg_time);
    imwrite("rotate180_image.jpg", rotate180_image);

    // 3.旋转270度，逆时针旋转90度
    // | 1 | 2 |      T       | 1 | 3 |     X轴镜像    | 2 | 4 |
    // ---------   ------->   ---------    ------->   ---------
    // | 3 | 4 |              | 2 | 4 |               | 1 | 3 |
    Mat rotate270_image(img_width, img_hight, CV_8UC3, rotate270_buffer);
    beg_time = get_time_interval();
    transpose(src_image3, src_image3); 
    flip(src_image3, rotate270_image, 0);
    end_time = get_time_interval();
    printf("transpose + flip 顺时针旋转270耗时: %ld\n", end_time - beg_time);
    imwrite("rotate270_image.jpg", rotate270_image);

    beg_time = get_time_interval();
    rotate(src_image4, rotate90_image, ROTATE_90_CLOCKWISE);
    end_time = get_time_interval();
    printf("rotate 顺时针旋转90耗时: %ld\n", end_time - beg_time);

    beg_time = get_time_interval();
    rotate(src_image5, rotate180_image, ROTATE_180);
    end_time = get_time_interval();
    printf("rotate 顺时针旋转180耗时: %ld\n", end_time - beg_time);

    beg_time = get_time_interval();
    rotate(src_image6, rotate270_image, ROTATE_90_COUNTERCLOCKWISE);
    end_time = get_time_interval();
    printf("rotate 顺时针旋转270耗时: %ld\n", end_time - beg_time);

    free(rotate90_buffer);
    free(rotate180_buffer);
    free(rotate270_buffer);
    return 0;
}


