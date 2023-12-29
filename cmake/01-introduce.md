# CMake 使用中的注意事项

## CMake的安装

## CMake使用中的技巧

我们默认查看该文档的人，已经掌握了cmake的基本命令，例如`cmake_minimum_required(VERSION 3.20)`，`add_executable(test main.cpp)`等，下面要介绍的主要是一些工程上的命令

### 1、工程版本号

通常情况下，我们在程序开发时，都需要提供版本号，如何提供版本号就成为了一个关键问题，我们以C++为例，最为简单的方式是提供一个`version.h`的头文件
