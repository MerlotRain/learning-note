# VCPKG ON OSX

在经历了一整天的折腾后，终于完成了MacOSX对C++开发环境的搭建

## homebrew

我最早接触的Mac OSX的包管理是 `homebrew`，这是当初学习`maven`的时候使用的，后来一直被我最为C++的包管理。

诚然，`brew`提供了非常简便的包获取方式，而且因为包都存在预编译的二进制文件，我在获取包的时候，几乎不会花费任何时间

但随着使用的深入，我发现`brew`越发难用了

### brew 的痛点

* 缺乏对多版本管理的灵活性

* 与 CMake 和 vcpkg 的整合不足

* 过于依赖最新版本

* 二进制依赖的兼容性问题

* 生态局限性

* 跨平台支持不足

基于以上的问题，它促使我终于更换到了vcpkg在macos下的开发支持

### vcpkg

首先要声明的是，brew再有问题，也不应该舍弃，我们只是舍弃了它作为C++包管理的功能，但是它的其他作用是非常好用的

首先我们需要使用brew来安装C++所需要的所有链条

```shell
brew install cmake
brew install ninja
brew install llvm
brew install meson
brew install automake
brew install libtool
brew install autoconf
brew install autoconf-archive
```
这些基本的模块是构建C++库的基础，因为vcpkg是下载源码进行编译的

当完成这些基本模块之后，我们再安装vcpkg

vcpkg的基本安装步骤不再陈述，这里只讲几个重要的点

* vcpkg最好先安装一些基础的库

例如 `curl`, `libiconv`, `zlib`, `libzip` 等等基础库

* vcpkg安装最好使用管理员

```shell
 sudo vcpkg install curl
```

* vcpkg安装完成后只需要两个配置

```shell

export PATH=.../vcpkg:$PATH

export CMAKE_PREFIX_PATH=.../vcpkg/installed/arm64-osx/share # 确保直接查找库

```