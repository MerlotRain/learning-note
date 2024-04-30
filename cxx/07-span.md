# span

`std::span`是`C++20`中的一个新特性，它提供了一种表示连续内存区域（如数组、向量或C风格数组）的固定大小或动态大小的视图的方式。

## 一、一块连续大内存的小内存

我们先考虑这样一种情况，有一组数据使用`std::vector`存储，请你掐头去尾，对剩下的元素求和

这似乎是个非常简单的功能，但却是一类问题，即对一块连续内存中的连续的一部分进行处理，这种情况下，我们通常会这么操作

```c++

void deal_with_pointer(const int* begin, const int* end)
{
    // 头指针和内存长度
}

void deal_with_iterator(const std::vector<int>::const_iterator begin, const std::vector<int>::const_iterator end)
{
    // 使用迭代器
}

```

这两个例子都展示了如何在没有`std::span`的情况下处理连续内存区域。然而，它们都存在一些缺点：

* 类型安全性：裸指针方法没有提供类型信息，这可能导致类型不匹配的错误。迭代器方法稍微好一些，因为它们与容器类型相关联。

* 接口复杂性：函数通常需要接受两个参数（开始和结束迭代器或指针），这增加了接口的复杂性。
  
* 与C风格数组的互操作性：裸指针方法可以更容易地与C风格数组一起使用，但迭代器方法则不然，因为C风格数组没有成员函数如 begin() 或 end()。



## 二、基本功能

我们先看一个例子来了解`span`的作用

```c++

void span_test(const std::span<int> &elements)
{
    for (auto &e : elements)
        e *= 2; // 编译成功，span的const引用仍然可以修改
}


void vector_ref_test(const std::vector<int> &elements)
{
    for (auto &e : elements)
        e *= 2; // 编译错误，因为vector是const引用
}

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::span<int> sp(vec);
    span_test(sp);
    std::for_each(vec.begin(), vec.end(), [](auto &i)
                  { std::cout << i << std::endl; });
    return 0;
}

```

这个例子里，我们创建了一个`span`对象用来管理`vec`对象，并对里面的元素都增大一倍。
由此引发了两个问题：

* `span`到底管理了什么
  
* `span`的管理是值还是引用
  
我们逐个来回答

`span`首先肯定是以绝对引用的方式管理了一块内存，它和`std::string_view`类似，引用一块内存但不掌握内存生命周期。

与`vector_ref_test`函数不同，`span`对象的`const &`只是规定了`span`自身的不可变，与数据的变化无关，数据是否不可变，与模板类型有关。

例如`std::span<int>`这种就是可变的。

`std::span<const int>`这种就是不可变的。

        
