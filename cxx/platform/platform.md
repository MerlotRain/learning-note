# 什么是Platform

`Platform`是平台，在`C/C++`开发过程中，我们经常需要和平台性质的函数打交道，比如`dlopen`,`getaddrinfo`等。

如果我们使用的`Qt`或者`Poco`这类的C++框架，很简单可以解决，但有这么两种情况。

* 服务器资源非常紧张，不允许我们引入一个庞大的开源框架

* 功能需求非常简单，不需要引入庞大框架

这两种情况下，掌握平台函数就至关重要，我们对平台函数的操作主要分为以下部分：

* 动态库加载[module]

* 网络相关接口[networkinterface]

* 共享内存[sharememory]

* 平台锁[lock]

* 平台线程[thread]

* 管道通信[pipe]

* 文件和文件夹相关[filesystem]
