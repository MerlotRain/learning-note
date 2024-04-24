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
            "miDebuggerPath": "gdb",
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
#include <windows.h> // 不需要去安装Windows SDK，这种文件是必然存在的，但是调用Windows API是否有影响，后续测试

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

```

```cmake

cmake_minimum_required(VERSION 3.18)

add_executable(code main.cpp)

```
