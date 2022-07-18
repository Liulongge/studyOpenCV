## 依赖
    1、opencv 4.5.2
    2、opencv_contrib 4.x
    tracker模块位于其中

## 源码下载
    opencv: https://opencv.org/releases/
    opencv_contrib: https://github.com/opencv/opencv_contrib

## 编译
    $ cd opencv-4.5.2
    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local -DOPENCV_GENERATE_PKGCONFIG=ON -DOPENCV_ENABLE_NONFREE=YES -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..

    DOPENCV_EXTRA_MODULES_PATH: 指明opencv_contrib路径

## 测试数据
    位于/tracker/test_data

## 编译
    $ cd tracker
    $ ./release

## 运行
    $ cd build
    $ ./demo [run_mode] [test_data_path]
    eg: ./demo MOSSE ../test_data/dance.mp4
    test on mac
