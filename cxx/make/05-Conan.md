# Conan

`Conan`是C/C++的一种第三方库管理工具，支持跨平台，目前主流的C++库都存在，可以说非常方便

## 一、安装

首先需要保证你的系统里存在Python，因为`Conan`是Python支持的，确定Python存在后使用如下命令

```sh
pip install conan

conan --version
```

正常输出后就代表安装成功了。

## 二、Conan如何管理包

现代开发语言中，对包管理都采用配置文件组织，比较典型的例如Java中的`maven`通过`pom.xml`管理依赖库，`Rust`中的`Cargo.tol`文件，`Python`中的`requirements.txt`。

`Conan`非常明显地采用了类`Python`风格。

## 三、编译
