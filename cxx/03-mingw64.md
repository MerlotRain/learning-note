# MinGW

MinGW，全称Minimalist GNU for Windows，是一个开源的软件开发环境，旨在为Windows操作系统提供GNU工具集的使用环境。它是GCC编译器和GNU Binutils在Win32平台下的移植产物，包括一系列头文件（Win32API）、库和可执行文件，允许程序员在Windows平台上使用GCC和其他GNU工具集来编写和编译C、C++等语言的程序。

## MinGW的主要功能包括：

* 提供GNU编译器集合（GCC）：包含C、C++、Objective-C等语言的编译器，能够将源代码编译成可在Windows上直接运行的二进制文件，而不需要依赖第三方C运行时库。

* 简化开发环境：MinGW提供了一个轻量级的开发环境，让程序员在Windows上体验到类似Linux的开发环境，减少了对Windows特有开发工具链的依赖。

* 原生Windows应用程序支持：MinGW的主要目标是让程序员能够在Windows操作系统上编译出原生的Windows应用程序，直接调用Win32 API，而非Linux API。

* 跨平台兼容性：通过MinGW编译的程序不仅可以在Windows上运行，还可以通过简单的修改在Linux或其他操作系统上运行，从而实现跨平台兼容性。

* MinGW还具有高度的可定制性，用户可以根据自己的需要选择安装特定的编译器和工具集。同时，由于其开源的特性，MinGW也吸引了大量的开发者为其贡献代码和修复bug，使其不断完善和发展。

## 为什么一定是MinGW

对我来说一个简单原因在于，MinGW的CMake编译结果，没有debug和release的套壳文件夹，这是非常nice的一点

# mingw-64环境搭建

在Windows下，我们为了使用gcc,g++等编译工具，使用mingw是必然的选择。

在此，考虑到Qt等环境，我推荐使用一下的安装方式

## 先完全卸载Visual Studio 2022

这里正常使用geek工具卸载就可以了。

## 安装Qt

我安装的Qt6.7.0，版本无所谓，关键是选择对应的MingW版本，以及Qt扩展部分的MingW，两个版本做到一致

## 开发与环境变量配置

* Qt的开发一切正常，在Qt Creator里面完全不用配置任何东西，正常安装之后就可以直接编译运行

* 配置MingW路径

>
> 假设说我们安装的Qt路径在 C:/Qt
>
> 那么配置MingW的路径到path C:/Qt/Tools/mingw_版本/bin
>

* 配置Qt的开发路径

>
> 这个没啥说的吧，添加三个路径到path中，C:/Qt/6.7.0/mingw_64/bin; C:/Qt/6.7.0/mingw_64/include; C:/Qt/6.7.0/mingw_64/lib
>

* 安装vcpkg，当然这个步骤也可以不要，自己编译需要的库也是可以的，但是建议还是使用吧，毕竟包管理方便了很多

>
> 此时需要下载mingw的编译库，所以需要配置两个环境变量
>
> VCPKG_DEFAULT_HOST_TRIPLET=x64-mingw-dynamic
>
> VCPKG_DEFAULT_TRIPLET=x64-mingw-dynamic
>
> 这两个环境变量主要的作用是指定下载什么编译器的包
>
> 之前我们需要这样写 `vcpkg install zlib:x64-windows` 这样配置之后直接写 `vcpkg install zlib`
>
> 配置完成后，我们为了更加方便的找到头文件以及动态库，可以继续将vcpkg的install目录下的`include` `lib` `bin` 配置到path里面去

* 安装VSCode作为编辑器

## VS Code下的几个重要文件

```json
# launch.json

{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) Launch",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/code.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb", #已经配置过路径，所以这里我们使用gdb调试
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }

    ]
}

```

```C++
// main.cpp

#include <iostream> // 这里的路径就正常找到mingw下的c++/include
#include <windows.h> // 不需要去安装Windows SDK，这些头文件都有MinGW提供，可以正常使用，包括类似shellapi.h等头文件

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

```

```cmake

# CMakeLists.txt

cmake_minimum_required(VERSION 3.18)

add_executable(code main.cpp)

```
