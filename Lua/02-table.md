# lua标准库函数

lua作为一门使用C语言开发的脚本，它的很多系统级别的函数都是C语言原生函数，例如`math.sin`,`io.open(filename[,mode])`。

熟悉C语言的同学应该很快反应过来，这种接口参数怎么和C语言如此相像。

这其实是lua底层封装的标准库，就是用lua机制调用标准函数，lua的`math`模块基本是全部调用`math.h`头文件，只扩展了一些常用的标准库没有的接口。

## 模块调用

有脚本语言编程经验的同学应该知道，调用的基本方式`mode.function(arguments)`。

## 基本函数

* assert
* error
* load
* ipairs
* tostring
* tonumber
* setmetatable
* select
* type
* xpcall

https://www.runoob.com/manual/lua53doc/manual.html#6.7

这些函数大部分都是辅助性质，他们不依赖于lua包，可以直接使用，非常好用。

## math

lua数学模块提供了基本的三角函数运算，常量，随机数等，比较简单，不再赘述

## io

文件读写模块，基本和C语言提供的方式一致，`open`,'flush`,`read`,`write`,`close`等。

这里必须吐槽一下NodeAPI，flush接口为什么要换个名字呢，不懂。

```lua

file = io.open("./hello.txt");

print(io.read());

io.close();
```

上述代码中，`open`打开了一个文件句柄，此时lua就持有了一个句柄，之后的操作全部在这个句柄上。可如果打开多个文件，那么就应该直接操作句柄。

```lua
file = io.open("./hello.txt");

file:read();

file:close();

```

这也是一种调用方式。

## string

lua提供的字符串处理模块，与C类似但也有区别。

这里做了很多扩展，提供了模式匹配能力，好用，但建议最好去阅读这部分源码

## utf8

提供utf8字符串处理基本能力。

## table

我们之前就说过，表本质是一个链表，不是二维表，所以这里面的函数都是链表操作基本。

## os

系统级的函数

* date 获取日期
* difftime 时间差
* execute 调用控制台执行

## coroutine