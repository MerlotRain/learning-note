# VSCode 搭建 Objective-C环境

## 为什么需要

如果我们是要开发Apple原生应用，那么我强烈建议使用Xcode实现，但对于C/C++的开发者来说，他们在开发跨平台应用时，可能需要使用Objective-C/C++来实现部分功能

例如Qt中就存在大量的`.m`和`.mm`文件，这些都是`OSX`系统才有的

对于这类应用，我们通常需要使用`CMake` 或 `Make`来管理，故，如果在`CMake`中引入Apple自带的库就很关键

如果你使用CMakeTool构建，然后在Xcode下编译，那么没有任何问题，你会找到你需要的库而不需要考虑配置，但如果在VSCode下呢

## VSCode需要的插件
* C/C++套件
* Clangd - 用于支持智能提示和代码跳转

## CMake的编写

我们的项目结构如下
> cala.c
> cala.h
> main.m
> CMakeLists.txt
>
> 其中main.m是Objective-C代码
> cala.c是C语言代码，定义了一个add函数，并在main.m中调用
>

```objective-c
#import <Carbon/Carbon.h>
#import <Foundation/Foundation.h>
#include "cala.h"

int main(int argc, const char * argv[]) {
    NSLog(@"Hello, World!");
    NSLog(sum(1, 2));
    return 0;
}
```


```CMake
# /System/Library/Frameworks

cmake_minimum_required(VERSION 3.20)
project(cmake-osx)

# This changes how find_xxx() commands work; the default is to find frameworks before
# standard libraries or headers, but this can be a problem on systems that have Mono
# installed, as it has a framework with the libjpeg and libpng  headers present -- so
# CMake finds the headers from Mono but the libraries from Homebrew, and hilarity ensues.
# Setting this to "last" means we always try the standard libraries before the frameworks.
set(CMAKE_FIND_FRAMEWORK LAST)

find_library(FOUNDATION_LIBRARY Foundation)
find_library(CARBON_LIBRARY Carbon)

add_executable(cmakeOSX main.m cala.c)
message("CARBON_LIBRARY=${CARBON_LIBRARY}")

target_include_directories(cmakeOSX PUBLIC ${CARBON_INCLUDE_DIR})
target_link_libraries(cmakeOSX ${CARBON_LIBRARY} ${FOUNDATION_LIBRARY})
```

