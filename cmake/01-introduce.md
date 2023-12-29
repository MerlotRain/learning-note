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
