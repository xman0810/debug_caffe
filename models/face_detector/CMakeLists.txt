cmake_minimum_required (VERSION 2.8)
project (test)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")
add_executable(face_detector face_detector.cpp)

#include_directories (/usr/local/include/opencv4)
#link_directories(/usr/local/lib)
set(LIBS opencv_stitching opencv_gapi opencv_dnn opencv_ml opencv_imgcodecs opencv_videoio opencv_video opencv_highgui opencv_objdetect opencv_flann opencv_imgproc opencv_features2d opencv_photo opencv_core opencv_calib3d)
target_link_libraries(face_detector ${LIBS})

