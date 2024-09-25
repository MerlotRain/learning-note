# ffmpeg

---

ffmpeg是一个开源的音视频处理库，可以说做音视频必须要掌握的库。

之前有需求要实现一个简单的视频播放器，虽然第一时间想到了ffmpeg，但在使用过程中出现了许多问题，所以换到了opencv

但opencv也有它的问题，例如部分视频播放失败（这是视频生成的问题），获取视频总时间、当前位置等接口不够直接等

当然，我们必须认识到，opencv的重点并不是视频领域，所以这些难点并不应该被放大

于是为了解决这些问题，我又重新开始学习了一下ffmpeg库，下面我将从一些基本的流程去讲述ffmpeg库的使用方法

## 一、安装

因为学习的需要，我这里并不建议使用源码安装，编译源码是一种能力，但在现代编程环境下，包管理已经越来越重要了，没必要自己再去编译源码

这里以MacOS为例，使用homebrew安装

```shell
brew install ffmpeg
```

在Windows下，可以使用vcpkg安装

```shell
vcpkg install ffmpeg
```

## 二、链接

我们使用CMake来管理项目，所以找到ffmpeg就非常重要

在Unix平台下，可以直接使用 pkg-config 来获取ffmpeg的链接信息

```cmake

find_package(PkgConfig REQUIRED)
pkg_check_modules(AVFORMAT REQUIRED libavformat)
pkg_check_modules(AVCODEC REQUIRED libavcodec)
pkg_check_modules(AVUTIL REQUIRED libavutil)
pkg_check_modules(AVDEVICE REQUIRED libavdevice)
pkg_check_modules(AVRESAMPLE REQUIRED libavresample)
pkg_check_modules(SWSCALE REQUIRED libswscale)
pkg_check_modules(SWRESAMPLE REQUIRED libswresample)


```

但是在Windows下，pkg-config并不存在，所以我们需要手动指定ffmpeg的链接信息

```cmake

find_package(AVFORMAT REQUIRED)
find_package(AVCODEC REQUIRED)
find_package(AVUTIL REQUIRED)
find_package(AVDEVICE REQUIRED)
find_package(AVRESAMPLE REQUIRED)
find_package(SWSCALE REQUIRED)
find_package(SWRESAMPLE REQUIRED)

```

除此之外，还可以自己写`FindFFMPEG.cmake`文件来管理ffmpeg的链接信息，可以参考[FindFFMPEG.cmake](./FindFFMPEG.cmake)

## 三、FFMPEG组件介绍

在开始之前，我们需要先了解一下ffmpeg的组件

ffmpeg的组件主要包括以下几个：

- libavformat：用于处理音视频的封装和解封装
- libavcodec：用于处理音视频的编解码
- libavutil：用于处理音视频的工具库
- libavdevice：用于处理音视频的设备
- libavresample：用于处理音视频的重采样
- libswscale：用于处理音视频的缩放
- libswresample：用于处理音视频的重采样
