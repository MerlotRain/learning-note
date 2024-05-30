# CMake Build

## 一、CMake再回归

c++的编译是个老大难的问题，因为有很多的平台，很多的编译器，很多的构建工具，而且不同平台还不一样，历史原因有很多，扯皮也有很多。

cmake的出现就是为了解决这个问题的，它是一个跨平台的编译工具，它使用一个配置文件来描述项目的编译规则，然后根据这个配置文件生成对应的makefile或者project文件，再由编译器进行编译。

## 二、Linux & MacOS

这是编译这件事情里最爽的平台，尤其是Linux

漂亮的包管理，强悍的gcc编译器，Ninja构建工具，cmake配置文件，make编译，完美！

MacOS平台下虽然提供了clang编译器，但很多开发人员还是会主动下载gcc，虽然我现在也用clang比较多，但总体来说没有大的变化。

区别主要还是在平台api上。

## 三、Windows

Windows的情况要复杂很多，首先是Windows平台自己的编译器、工程组织、构建工具。

从开发来看，如果我们专注与Windows平台的开发，使用`vcproj`是完全没有问题的，但是跨平台的软件越来越重要，至少对国内的工业软件，跨平台似乎成了“必须”的事情。

此时，使用`CMake`来管理工程就是再方便不过了。

## 3.1 编译器的选择

Windows下有两个主流的编译器，`MSVC`和`MinGW`，这两者我都有使用，`MSVC`是微软官方的编译器，`MinGW`是Minimalist GNU for Windows的缩写，它是一个GNU编译器集合，其中就包括`gcc`，`g++`，`gdb`等，它是一个跨平台的编译器，可以编译出Windows、Linux、MacOS等平台的程序。

这两者我都有使用过。

如果但从跨平台性质来看，使用`MinGW`是合理的，但是如果结合`C++包管理`的问题，我个人推荐`MSVC`。

因为Windows平台下最好的包管理就是`vcpkg`，它是微软出的，对微软自家的编译器和编辑器都有很好的支持，一家人不说两家话嘛。

同时，我现在也在学习有关`WinRT`的知识，所以使用`MSVC`模块是个非常好的选择。

## 3.2 MSBuild

我们在`Visual Studio`中创建项目生成的`sln`和`vcproj`都是由`MSBuild`创建的。

在`CMake-GUI`中构建，也会创建出一大堆上述文件，可这个东西带来了一个很不爽的，和Linux不一样的东西。

编译结果会放在带`CMAKE_BUILD_TYPE`的文件夹下，比如`Debug`和`Release`，而`MSBuild`会创建一个`bin`文件夹，里面放的就是编译结果，而且`bin`文件夹下会创建一个`Debug`和`Release`文件夹，里面放的就是编译结果。
    
这真不是一件让人愉快的事情，因为这给部分不熟悉CMake的人带来很多链接的bug。

怎么处理这个问题

既然是MSBuild引起的，自然要替换`MSBuild`，我们就想到了`Ninja`。

```json
    "cmake.generator": "Ninja",
    "cmake.configureArgs": [
        "-DCMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe",
        "-DCMAKE_CXX_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.39.33519/bin/Hostx64/x64/cl.exe",
        "-DCMAKE_GENERATOR:STRING=Ninja"
    ]
```

首先自然是配置`Ninja`的路径，然后是配置MSVC的编译器，这样就可以正常编译了。
