# Version : 0.0.1
FROM ubuntu:18.04
MAINTAINER Quan Xiao "xiaoquan9653@163.com"
LABEL maintainer xmantou0810@163.com
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    vim \
    cmake \
    build-essential \
    wget \
    libboost-system-dev \
    libboost-thread-dev \
    libboost-regex-dev \
    libboost-filesystem-dev \
    libgflags-dev libgoogle-glog-dev liblmdb-dev \
    libprotobuf-dev protobuf-compiler libhdf5-dev \
    libleveldb-dev libsnappy-dev \
    python python-numpy \
    python-pip git \
    libboost-all-dev \
    ninja-build \
    libopenblas-dev libblas-dev libatlas-base-dev \
    python-matplotlib \
    python-skimage python-protobuf \
    gdb \
    python-pathlib \
    unzip

RUN rm -rf /var/lib/apt/lists/*
#RUN pip install opencv-python
#RUN pip install cython -i https://pypi.mirrors.ustc.edu.cn/simple/
#RUN pip install tqdm -i https://pypi.mirrors.ustc.edu.cn/simple/
#RUN pip install pycocotools  -i https://pypi.mirrors.ustc.edu.cn/simple/

ARG opencv_version=3.4.1
ENV OPENCV_DIR /opt/opencv
RUN mkdir -p $OPENCV_DIR
WORKDIR $OPENCV_DIR
RUN wget --no-cache https://github.com/Itseez/opencv/archive/${opencv_version}.zip -O opencv-${opencv_version}.zip
RUN unzip opencv-${opencv_version}.zip && \
    cd opencv-${opencv_version} &&\
    mkdir build && cd build && \
    cmake -D CMAKE_BUILD_TYPE=Release \
    -D CMAKE_INSTALL_PREFIX=$(python -c "import sys; print(sys.prefix)") \
    -D WITH_TBB=ON \
    -D WITH_V4L=ON \
    -D WITH_CUDA=OFF \
    -D WITH_EIGEN=OFF \
    -D WITH_OPENCL=OFF \
    -D BUILD_opencv_python3=YES \
  ..

RUN cd opencv-${opencv_version}/build && \
    make -j"$(nproc)" && \
    make install && \
    rm $OPENCV_DIR/opencv-${opencv_version}.zip

ENV CAFFE_DIR /opt/caffe
RUN mkdir -p $CAFFE_DIR
WORKDIR $CAFFE_DIR
RUN wget --no-cache https://github.com/BVLC/caffe/archive/master.zip -O caffe.zip
RUN unzip caffe.zip && \
    cd caffe-master && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Debug -DCPU_ONLY=ON \
    ..

RUN cd caffe-master/build && \
    make && make install

RUN rm $CAFFE_DIR/caffe.zip
COPY read_proto ./read_proto
EXPOSE 80
