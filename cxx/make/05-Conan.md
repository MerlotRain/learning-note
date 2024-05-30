# Conan

`Conan`是C/C++的一种第三方库管理工具，支持跨平台，目前主流的C++库都存在，可以说非常方便

## 一、安装

首先需要保证你的系统里存在`Python`，因为`Conan`是`Python`支持的，确定`Python`存在后使用如下命令

```sh
pip install conan

conan --version
```

正常输出后就代表安装成功了。

## 二、Conan如何管理包

现代开发语言中，对包管理都采用配置文件组织，比较典型的例如Java中的`maven`通过`pom.xml`管理依赖库，`Rust`中的`Cargo.toml`文件，`Python`中的`requirements.txt`。

`Conan`非常明显地采用了类`Python`风格，即使用一个配置文件来描述程序的依赖包及包版本，再统一下载这些以来环境。

它有两种形式，复杂点的是`conanfile.py`，简单点的是`conanfile.txt`，这里以`conanfile.txt`为例。

作为一个强大的包管理神器，它集成了包下载、编译、测试等所有操作，我们在后续逐步讲解。

## 三、`requirefile.txt`

`requirefile.txt`是`Conan`的配置文件，它使用`txt`格式，文件内容如下

```txt
[requires]
# 依赖包
# 格式：包名/版本
# 例如：zlib/1.2.11
zlib/1.2.11

# 依赖包的依赖
# 格式：包名/版本
# 例如：zlib/1.2.11
zlib/1.2.11
