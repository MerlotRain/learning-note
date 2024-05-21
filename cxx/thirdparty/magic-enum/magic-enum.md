# Magic Enum

在做数据的序列化与反序列化中，我们经常会遇到这样的问题

假设我们要将一个`Symbol`对象序列化成`json`格式，那么`Symbol`中枚举`SymbolType`以什么样的方式写入

很多情况下我们会选择利用枚举和`int`的关系来确定

```C++

enum Color {
    Black,
    Red,
    Green
};

void output()
{
    Color c = Color::Green;
    std::cout << (int)c << std::endl;
}

```

这种情况下带来了两个严重的问题

* 现在我要在`Black`之前再加一个颜色枚举，例如`Blue`，那么下一次读进来的时候，颜色就变成了`Blue`，这就属于非常严重的错误了，因为数据发生变化了。

* 对于维护人员（枚举是配置项，或者枚举信息以日志输出）来说，他们也无法理解这个东西到底是什么，要如何修改

从这种角度讲，`int`肯定是不行的，将枚举的文字写出来最好，例如：

```C++

enum LogLevel
{
    INFO,
    WARN,
    ERROR,
};

// 输出的日志的时候格式为[INFO] xxxxxxx

```

# 解决方案

### 传统解决方案

提供两个函数，用于枚举与字符串的转换

```C++

LogLevel toEnum(const std::string& str)
{}

std::string toString(const LogLevel& level)
{}

```

这个不错，但是如果将来枚举需要维护，函数也必须维护

### 枚举模板映射

创建枚举和字符串的静态映射关系

```C++


```

### 使用magic_enum库

在讲述这里之前，我们先看看`Java`和`Rust`是怎么处理的

```Java

public enum MyEnum {  
    VALUE1,  
    VALUE2;  
}  
  
public class EnumToStringExample {  
    public static void main(String[] args) {  
        MyEnum value1 = MyEnum.VALUE1;  
        System.out.println(value1.name()); // 输出: VALUE1  
    }  
}
  
public class StringToEnumExample {  
    public static void main(String[] args) {  
        String enumName = "VALUE1";  
          
        try {  
            MyEnum myEnum = Enum.valueOf(MyEnum.class, enumName);  
            System.out.println(myEnum); // 输出: VALUE1   
        } catch (IllegalArgumentException e) {  
            System.out.println("No enum constant with name: " + enumName);  
        }  
    }  
}

```


```rust

enum MyEnum {  
    Variant1,  
    Variant2,  
    Variant3,  
}

impl MyEnum {  
    fn to_string(&self) -> &str {  
        match *self {  
            MyEnum::Variant1 => "Variant1",  
            MyEnum::Variant2 => "Variant2",  
            MyEnum::Variant3 => "Variant3",  
        }  
    }  
}  
  
fn main() {  
    let value = MyEnum::Variant2;  
    let string_representation = value.to_string();  
    println!("{}", string_representation); // 输出: Variant2  
}



impl MyEnum {  
    fn from_string(s: &str) -> Result<MyEnum, &'static str> {  
        match s {  
            "Variant1" => Ok(MyEnum::Variant1),  
            "Variant2" => Ok(MyEnum::Variant2),  
            "Variant3" => Ok(MyEnum::Variant3),  
            _ => Err("Unknown variant"),  
        }  
    }  
}  
  
fn main() {  
    let string_representation = "Variant2";  
    match MyEnum::from_string(string_representation) {  
        Ok(value) => println!("Converted to {:?}", value), // 输出: Converted to Variant2  
        Err(e) => println!("Error: {}", e), // 如果字符串不匹配任何变体，将打印错误消息  
    }  
}

```

  
