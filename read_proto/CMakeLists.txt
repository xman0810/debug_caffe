cmake_minimum_required (VERSION 2.8)
 
project (test)
set(CAFFE_PATH "/opt/caffe/caffe-master/build/install")
option (CPU_ONLY "Use tutorial provided math implementation" ON)
set(CMAKE_CXX_FLAGS "-DCPU_ONLY=1")
set(CMAKE_BUILD_TYPE Debug)
add_executable(read_caffemodel read_caffemodel.cpp)
   
include_directories ( ${CAFFE_PATH}/include
                      /opt/caffe/include
                      /usr/local/include
                      /usr/local/cuda/include
                      /usr/include )
                
target_link_libraries(read_caffemodel
                      ${CAFFE_PATH}/lib/libcaffe-d.so
                      /usr/lib/x86_64-linux-gnu/libglog.so
                      /usr/lib/x86_64-linux-gnu/libboost_system.so)

