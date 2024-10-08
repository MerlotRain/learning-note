# Lua Base

## 一、基本数据类型

`Lua`的基本数据类型有8个

|数据类型|描述|
|-|-|
|nil|类似`NULL`，代表空|
|number|数值，包含整数、小数等一切数|
|string|字符串，由单引号或双引号引用的一串字符，通常使用双引号|
|boolean|只有`true`和`false`，在`Lua`中只有`nil`是`false`，`0`也是`true`|
|function|包括`C`和`Lua`定义的一切函数|
|userdata|表示任意存储在变量中的C数据结构|
|thread|表示执行的独立线路，用于执行协同程序|
|table|最重要的结构，本质是一个关联数组|

## 二、变量

### 2.1 变量初值

`Lua`中所有变量的初值都是`nil`

### 2.2 全局变量

我们以最简单的数学计算入手。

```Lua
a = 5
b = 10
print(a + b)
```

假设我们的程序需要运算上面的语句，那么我们必须知道`a`和`b`的值，所以需要在某处存储这两个变量的值。

`Lua`作为一个脚本语言，我们所有的操作都在`Lua`程序上，那么这个程序就需要记录这两个值，所以`Lua`开辟了一个叫做`_G`的全局表来记录这些变量，这种行为类似我们在`C语言`中通过读取用户输入的两个`int`进行求和一样，同样需要开辟一块内存存储两个`int`。

所以上述代码也可以改为:

```Lua
_G.a = 5
_G.b = 10
print(_G.a + _G.b)
```

### 2.3 局部变量

局部变量主要用`local`来标记，它会在作用域结束的时候失效，即重新标记为`nil`.

