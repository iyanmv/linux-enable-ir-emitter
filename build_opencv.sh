#!/bin/sh
version=4.7.0

wget -O opencv.zip https://github.com/opencv/opencv/archive/${version}.zip
unzip opencv.zip

mkdir -p opencv-4.7.0/build && cd opencv-${version}/build

cmake .. -DBUILD_SHARED_LIBS=OFF -DBUILD_LIST=videoio -WITH_V4L=ON\
    -DOPENCV_GENERATE_PKGCONFIG=YES -DCMAKE_INSTALL_PREFIX=./install_dir \
    -DWITH_JPEG=OFF -DWITH_PNG=OFF -DWITH_TIFF=OFF -DWITH_WEBP=OFF -DWITH_OPENJPEG=OFF -DWITH_JASPER=OFF -DWITH_OPENEXR=OFF -DWITH_IMGCODEC_HDR=OFF -DWITH_IMGCODEC_SUNRASTER=OFF -DWITH_IMGCODEC_PXM=OFF -DWITH_IMGCODEC_PFM=OFF \
    -DWITH_FFMPEG=FALSE -DWITH_GSTREAMER=OFF -DWITH_1394=OFF -DDVIDEOIO_ENABLE_PLUGINS=OFF -DWITH_ANDROID_MEDIANDK=OFF \
    -DWITH_GTK=OFF -DHIGHGUI_ENABLE_PLUGINS=OFF -DWITH_VTK=OFF \
    -DWITH_PROTOBUF=OFF -DOPENCV_DNN_OPENCL=OFF \
    -DWITH_VA_INTEL=OFF -DWITH_OPENCL=OFF -DWITH_OPENCL_SVM=OFF -DWITH_OPENCLAMDFFT=OFF -DWITH_OPENCLAMDBLAS=OFF -DWITH_OPENCL_D3D11_NV=OFF \
    -DWITH_IPP=OFF -DWITH_CAROTENE=OFF -DWITH_CPUFEATURES=OFF -DWITH_EIGEN=OFF -DWITH_OPENVX=OFF -DWITH_DIRECTX=OFF -DWITH_VA=OFF -DWITH_LAPACK=OFF -DWITH_QUIRC=OFF

make && make install