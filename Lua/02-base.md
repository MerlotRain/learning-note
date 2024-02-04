# Lua 基本数据结构

## 注释
```lua

-- // signle-line comment

--[[
    // multi-line comment
]]--

```

## 变量命令

与其他语言一致的规范，这种东西不需要创新，做到见明知意就行

## 关键字

and,break,do,else,elseif,end,false,for,function,if,in,local,nil,not,or,repeat,return,then,true,until,while,goto

## 变量命令

与其他语言一致的规范，这种东西不需要创新，做到见明知意就行

## 关键字

and,break,do,else,elseif,end,false,for,function,if,in,local,nil,not,or,repeat,return,then,true,until,while,goto

## 全局变量

脚本语法的特点，没有特殊说明的就是全局变量，这似乎和语言底层的实现有关

## 基本数据类型

### nil

空值，类似C语言中的`NULL`，很重要，在lua中，只有`nil`和`false`代表假，其他都是真

### boolean

只有`true`和`false`两个

### number

脚本语言的经典了，一个number代替所有的数字类型，也能理解，都已经用脚本了，谁还关注性能问题，方便快捷才是根本

### string

代表一段字符

### table

```lua
local tab1 = {}
local tab2 = {"Apple", "MS", "Google"}
```

本质是一个关联数组，你可以理解为这就是一个结构体的数组
```C++
struct tableItem {
    void* key;
    void* data;
}
typedef std::vector<tableItem> table;
```

我们往表里面添加数据，即使在添加`data`部分，key如果么有传，则默认自增，如果传了就使用传入的值

虽然我们可以给`key`任意值，但是正常情况下，写入无规律的任意值有点弱智

### function

遵循脚本语言的`函数是一等公民`，基本的语法是`function fun_name(args...) { fun body }`

### thread 

协程

### userdata

用户自建类型，主要是C/C++的数据类型
