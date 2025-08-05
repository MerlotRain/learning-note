# vcpkg使用说明

## 1. vcpkg下载的库链接方式

以vscode为例，只需要在`settings.json`中配置如下内容

```json
{
    "cmake.configureArgs": [
         "-DCMAKE_TOOLCHAIN_FILE=D:/vcpkg/scripts/buildsystems/vcpkg.cmake",
    ]
}
```

其实完全没有必要将`vcpkg`安装目录的`bin`,`lib`,`include`,`share`等文件夹配置处理，这样很无语，只需要正常配置`CMAKE_TOOLCHAIN_FILE`即可。

我的建议是将`CMAKE_TOOLCHAIN_FILE`的设置交给各个开发人员来完成，如果在公司开发为了一键配置，那么可以如下处理

```txt

cmake_minimum_required (VERSION 3.10)
set(VCPKG_ROOT "" CACHE PATH "Path to the vcpkg installation directory")
if(NOT VCPKG_ROOT)
  message(FATAL_ERROR "VCPKG_ROOT must be set. Please specify the vcpkg root directory.")
endif()

# 这一行一定要在project命令之前写，否则部分库，例如OpenSSL会出现链接问题
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE PATH "Vcpkg toolchain file")


```

## 2. vcpkg 基线包管理
