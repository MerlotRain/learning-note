# MacOS 安装配置 homebrew

## homebrew

从`GPT`的介绍如下：

>
> Homebrew是一款在Mac OS及Linux等操作系统平台下的开源软件包管理工具。它拥有安装、卸载、更新、查看、搜索等众多实用的功能，可以大大简化软件管理的流程，提高用户的工作效率。通过简单的终端指令，Homebrew就能够自动处理软件的安装、升级和卸载等操作，而无需用户关心各种依赖和文件路径的问题。
> 
> Homebrew的主要优势在于其简单易用、灵活可定制化以及速度快等特点。它可以从源码包解压并自动配置好各种环境变量，同时自动解决软件包的依赖问题。而且，Homebrew下载和安装的软件
> 
> 全部来自对应的软件官网，用户可以放心使用，无需担心软件的安全性问题。
>
> 在Mac上，Homebrew可以管理系统自带的软件和第三方软件，帮助用户快速找到并安装需要的软件，提高了MacOS的使用体验。无论是开发者还是普通用户，都可以通过Homebrew轻松地管理和维护他们的软件系统。
>

## homebrew安装

关于homebrew的安装，直接使用官方提供的命令

```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## homebrew的安装位置

在`x86`架构下，`homebrew`正常是安装在`/usr/local/`下面的，但是在`arm64`架构下，它会安装到`/opt/homebrew/`下面，相关安装脚本如下

```sh

  if [[ "${UNAME_MACHINE}" == "arm64" ]]
  then
    # On ARM macOS, this script installs to /opt/homebrew only
    HOMEBREW_PREFIX="/opt/homebrew"
    HOMEBREW_REPOSITORY="${HOMEBREW_PREFIX}"
  else
    # On Intel macOS, this script installs to /usr/local only
    HOMEBREW_PREFIX="/usr/local"
    HOMEBREW_REPOSITORY="${HOMEBREW_PREFIX}/Homebrew"
  fi
  HOMEBREW_CACHE="${HOME}/Library/Caches/Homebrew"

```

这就带来了一个很恶心的问题，如果正常安装在`/usr/local/`下，我们安装的库的头文件是可以直接找到的，但是`/opt/homebrew/`不是一个系统可以识别的路径，操蛋

为此，我尝试去下载脚本修改后在本地直接运行，还是不行

## 为什么要这样

从homebrew的官方说法来看，换到`/opt/homebrew/`是为了和系统环境隔离开，这样可以最大限度地避免污染环境，这的确是个非常nice的说法

我们都知道，MacOS的开发环境有这样几个神坑

* `clang`编译器，很牛逼，但我们还是会对`gcc`有需求

* `make`版本落后，这个历史原因大家自己找，但是正常新Mac的`make`版本应该都是`3.81`

* `bash`版本落后，这个也是历史原因，版本开源协议引起的，所以新Mac的`bash`版本是`3.2.57(1)-release`，很多脚本级的调试有问题

这些都导致，我们在使用`homebrew`后，会选择主动安装`gcc`,`make`,`bash`

所以隔离是应该的，必要的，正确的

如何替换，或者说更加优雅的替换，后续会在其他篇章介绍

## 环境搭建

### CMake

我个人对于`CMake`很不建议使用`brew`安装，我觉得这是一个非常底层的工具，使用`brew`安装，就会出现某一天突然被升级，导致一些配置需要重新配，所以`CMake`最好使用源码编译，直接`make install`到`user/local/bin`里面

### 解决VSCode直接找头文件

虽然我们可以通过修改`CMake`的`configureArgs`指定库路径，但这种东西能不写就不写

我们可以通过以下几个环境变量解决

```sh
# ~/.bash_profile

export C_INCLUDE_PATH=/opt/homebrew/include:$C_INCLUDE_PATH

export CPLUS_INCLUDE_PATH=/opt/homebrew/include:$CPLUS_INCLUDE_PATH

export LIBRARY_PATH=/opt/homebrew/lib:$LIBRARY_PATH

export LD_LIBRARY_PATH=/opt/homebrew/lib:$LD_LIBRARY_PATH

```

### Zshrc

我非常建议大家使用`zshrc`去管理环境变量

这里面我只主动配置了两句

* `homebrew`的`bin`路径到`PATH`里面

* 一句脚本

```sh
source ~/.bash_profile
```

其他所有的环境变量我都建议直接写到`~/.bash_profile`中，包括你安装的`MySQL`,`Go`,`Zig`,`maven`等等环境

因为`zshrc`的`source`是系统处理的，我们让它协助处理`source ~/.bash_profile`就ok了
