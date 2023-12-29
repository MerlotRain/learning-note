# CMake 使用中的注意事项

## CMake的安装

## CMake使用中的技巧

我们默认查看该文档的人，已经掌握了cmake的基本命令，例如`cmake_minimum_required(VERSION 3.20)`，`add_executable(test main.cpp)`等，下面要介绍的主要是一些工程上的命令

### 1、工程版本号

通常情况下，我们在程序开发时，都需要提供版本号，如何提供版本号就成为了一个关键问题

#### 1.1 CMake工程版本号

在cmake中，通常我们可以用`project(test VERSION 1.0.1)`的方式来设置工程的版本号

#### 1.2 C++中的版本号

```c++
#ifndef VERSION_H
#define VERSION_H

#define CORE_VERSION_MAJOR 1
#define CORE_VERSION_MINOR 0
#define CORE_VERSION_PATCH 1

#define CORE_VERSION_STRING "1.0.1"

#endif //VERSION_H
```

这种一种最为简单的处理方式，与以上最大的区别在于，我们在代码中可以通过`#include <version.h>`的方式读取定义的版本宏，并作出相应的操作，例如依据版本判断执行的代码块
但它同样存在一个问题，定义在`version.h`中的宏，无法在CMake中用做条件判断。例如我们在Qt开发中会判断Qt的大版本是5还是6，于是就有了第三种解决方案。

#### 1.3 CMake configure_file

首先我们需要在代码中定义一个`version.h.in`的模板文件
```C++
#ifndef VERSION_H
#define VERSION_H

#define CORE_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define CORE_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define CORE_VERSION_PATCH @PROJECT_VERSION_PATCH@

#define CORE_VERSION_STRING "@PROJECT_VERSION@"

#endif //VERSION_H
```

在`CMakeLists.txt`，通常是最外层，添加如下内容
```CMake
project(test VERSION 1.0.1)
configure_file(version.h.in version.h)
```

在经过CMake configure之后，就会在`${PROJECT_BINARY_DIR}`下生成`version.h`文件

经过了上面的操作，我们成功实现了CMake动态生成程序版本号，同时该版本号也可以在CMake configure时，作为configure条件使用，整合了两种需求。

#### 1.4 方案扩展

在上述的方案中，仍然存在一些不灵活的地方，当我们更新了一个版本后，就要手动修改CMakeLists文件，虽然代价很大，但仍然有其他解决方案来避免手动修改CMakeLists

我们可以添加一个名为`VERSION.txt`的文本文件，将版本信息，软件名称，版权信息等都卸载文本中，在CMakeLists中，通过读文件的方式获取所需的值，如此，我们每次都只需要修改文本文件即可。


```txt
# VERSION.txt
# CORE versions
CORE_VERSION_MAJOR=1
CORE_VERSION_MINOR=0
CORE_VERSION_PATCH=1
```

```CMake

file(READ VERSION.txt _version_)
string(REGEX MATCH "CORE_VERSION_MAJOR=([0-9]+)" _ ${_version_})
set(_version_major ${CMAKE_MATCH_1})
string(REGEX MATCH "CORE_VERSION_MINOR=([0-9]+)" _ ${_version_})
set(_version_minor ${CMAKE_MATCH_1})
string(REGEX MATCH "CORE_VERSION_PATCH=([0-9]+)" _ ${_version_})
set(_version_patch ${CMAKE_MATCH_1})

project(test VERSION "${_version_major}.${_version_minor}.${_version_patch}")
unset(_version_)
unset(_version_major)
unset(_version_minor)
unset(_version_patch)

configure_file(version.h.in version.h)

```

### 2. C++函数导出定义

在C++开发中，API函数都需要提供导出头，在Windows平台下，我们需要定义 `__declspec(dllexport)`，对于API的调用方，则会使用 `__declspec(dllimport)`

在UNIX平台下，导出和导入都定义为`__attribute__((visibility("default")))`，通常我们有以下几种处理方式

#### 2.1 主动定义
```C++

#pragma once

#ifdef _WIN32
    #ifdef CORE_LIBRARY_BUILD
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#else
#define CORE_API __attribute__((visibility("default")))
#endif

```

这是一种简单的定义，主要区分了Windows平台和非Windows平台，在Qt中，也有另外一种常见的写法
```C++
// core_global.h

#ifndef CORE_GLOBAL_H
#define CORE_GLOBAL_H

#include <QtCore/QtGlobal>

#ifdef CORE_LIBRARY
#define CORE_API Q_DECL_EXPORT
#else
#define CORE_API Q_DECL_IMPORT
#endif

#endif //CORE_GLOBAL_H
```

通过源码我们可知，Qt根据平台，将相应的导出、导入定义已经做了封装，我们只需要对宏重命名即可，这两个例子中，`CORE_LIBRARY_BUILD`和`CORE_LIBRARY`都定义在工程中
例如.vcxproj，.pro，CMakeLists.txt中

#### 2.2 CMake主动生成

从上面例子中我们可以看出，导出头的内容和编译平台有关。

所以CMake提供了一种通用的处理方式，它定义在`GenerateExportHeader`中。

使用方式如下：

```CMakeLists
# 工程中的做法是，在最外层的CMakeLists.txt中添加模块

include(GenerateExportHeader)

# 在子模块中，例如 corelib 模块中，主动生成，以下是 corelib 中的内容

add_library(core SHARED)

generate_export_header( 
    core
    BASE_NAME core
    EXPORT_FILE_NAME core_global.h
)

target_include_directories(core PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}
)

```

在C++中就可以如下使用
```C++

#include <core_global.h>

class CORE_EXPORT Foo {};
```

