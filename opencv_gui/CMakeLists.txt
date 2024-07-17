# cmake needs this line
cmake_minimum_required(VERSION 3.1)

# 设置C++标准为C++11  
set(CMAKE_CXX_STANDARD 11)  
set(CMAKE_CXX_STANDARD_REQUIRED True)  
  

# Define project name
project(opencv_gui_project)

# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

# If the package has been found, several variables will
# be set, you can find the full list with descriptions
# in the OpenCVConfig.cmake file.
# Print some message showing some of them
# message(STATUS "OpenCV library status:")
# message(STATUS "    config: ${OpenCV_DIR}")
# message(STATUS "    version: ${OpenCV_VERSION}")
# message(STATUS "    libraries: ${OpenCV_LIBS}")
# message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")

link_directories(/Users/runge.liu/Documents/code/opencv4/opencv/build/lib)  
# Declare the executable target built from your sources
add_executable(opencv_gui main.cpp)

include_directories(  
    PRIVATE  
    /Users/runge.liu/Documents/code/opencv4/opencv/include
    /Users/runge.liu/Documents/code/opencv4/opencv/build/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/core/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/calib3d/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/features2d/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/flann/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/dnn/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/highgui/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/imgcodecs/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/videoio/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/videoio/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/imgproc/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/ml/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/objdetect/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/photo/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/stitching/include/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/gapi/include/opencv2/
    /Users/runge.liu/Documents/code/opencv4/opencv/modules/video/include/
)  
# Link your application with OpenCV libraries
target_link_libraries(opencv_gui PRIVATE libopencv_world.dylib)
