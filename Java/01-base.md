# Java 基础知识

## 一、数据类型

### 1.1 基本数据类型

- 整型：byte、short、int、long
- 浮点型：float、double
- 字符串：String
- 布尔型：boolean
- 数组：Array

### 1.2 引用数据类型

- 对象：Object
- 引用数据类型：类、接口

## 二、类的基本知识

- 父类转子类

```java
class A extends B
{

}

void foo(B b)
{
    // 建议向下时先判断
    if(b instanceof A) {
        // do something
        A a = (A)b;
    }
}
```
