# Thread

本文主要介绍C++11及以后的`std::thread`相关的类与函数

对线程部分主要讲述以下几点内容

* 线程创建和运行

* 线程同步

* 线程相关的简单操作


## 线程创建

### 一、创建`std::thread`

`std::thread`的创建通常来说非常简单，我们只需要将一个函数放到线程中并执行即可

```c++

int fun()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "thread fun..." << std::endl;
    return 0;
}

int main()
{
    std::thread th(fun);
    th.detach();
    return 0;
}

```

`std::thread`的主要接口有`detach`,`join`,`joinable`,``hardware_concurrency`

`detach`：主线程阻塞到子线程执行完成

`join`：主线程继续执行，子线程自己执行，自己结束，如果没有其他变量去记录，那么基本无法捕获线程结束，主要用于一些不需要关系结果的操作，比如写日志

`joinable`：判断这个线程是否可以被`join`

`hardware_concurrency`：获取系统支持的并发线程数，在多线程的情况下用得多，单个子线程其实没啥子必要

### 二、`std::future` & `std::promise`

`future`和`promise`是C++11之后提供的非常重要的线程操作

我们可以举一个例子：

>
> A同学下楼取快递，他向B同学承诺`promise`我等会儿上楼的时候给你带瓶水，那么在A同学`promise`的瞬间，B同学就获得了一个**水**这样一个`future`
>
> 那么B同学就可以一直等到A同学上楼
>
> 但是有个疑问，A同学一定会带一瓶水吗，答案是不一定。
>
> 因为可能发生很多情况，让A同学带水失败，比如超市关门了。
>
> 所以B同学的`future`可能是一个错误，也就是失败
>
> 那如果带水成功了，那么B同学从A同学那里获取了水，此时如果C同学找A同学也要水，因为只有一瓶，C必然获取失败
>
> 也就是说这个`future`是独享的
> 
> 但如果A同学带回来的是一条消息，那么消息就可以和C同学分享
> 
> 那么这个`future`就是共享的
>

这个例子虽然简单，但基本涵盖了`future`和`promise`的全部内容，接下来我们用代码简单演示

```C++

// 指针传递
int fun1(std::promise<int> *prom) 
{
    try
    {
        throw std::runtime_error("An error occurred during computation");
        prom.set_value(10);
    }
    catch (...)
    {
        // 捕获所有异常，并通过 std::promise 设置异常
        prom.set_exception(std::current_exception());
    }
}


// 右值引用
int fun2(std::promise<int> &&prom)
{
    prom.set_value(10);
    return 0;
}

// 引用
int fun3(std::promise<int> &prom)
{
    prom.set_value(10);
    return 0;
}

int main()
{
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    // 一般情况下我们使用指针的方式传递
    std::thread t(fun1, &prom);
    // 如果是右值参数，则需要使用std::move
    // std::thread t(fun2, std::move(prom));
    // 如果是引用，则需要使用std::ref去包一层引用
    // std::thread t(fun3, std::ref(prom));

    try
    {
        int value = fut.get();
        std::cout << "Value: " << value << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }

    t.join();
    std::cout << value << std::endl;
    return 0;
}

```

>
> 可以看到上面的例子和我们的小故事差不多
> 
> 先有承诺，承诺瞬间形成未来
> 
> 承诺可能失败，未来不存在，捕获异常
> 

### 三、`std::async`异步

`std::async`是一种更为轻便的异步操作

从上述例子我们可以看到`std::future`的强大，但每次写`promise`还是太麻烦了，即使在`lambda`表达式中也非常麻烦，所以`std::async`真的很香

直接看例子

```c++

int main()
{
    auto fun = []()->int { return 1; };

    std::future<int> fut = std::async(std::launch::async, fun);
    
    int value = fut.get();

    std::cout << value << std::endl;

    return 0;
}
```

这是更加简单的操作，关键是如何理解`std::async`的第一个参数

这个参数是一个枚举，有两个状态，`async`和`deferred`.

* `async` 表明异步直接执行

* `deferred` 表明异步先不执行，等到调用`future`的`get`或者`wait`的时候再执行，属于懒加载

## 线程同步

线程同步主要是说，在一个线程操作内存中的数据时，其他线程不应该操作，需要等这个线程操作完了再操作，主要涉及的是锁、信号量、条件变量、事件等重要概念

### 一、`std::mutex`相关

`std::mutex`是一个标准的最简单的锁，它将控制一块数据的访问

```C++

std::mutex mtx;

void increment_counter() {  
    
    mtx.lock();  
      
    for (int i = 0; i < 1000; ++i) {  
        ++counter;  
    }  
    mtx.unlock();  
} 

```

这个例子就表示了访问的时候加锁，访问结束解除锁

但有个问题，如果这段代码逻辑非常复杂，有很多`if`导致函数中途结束，那么我们每个`return`都要调用`mtx.unlock();`，如果有一处忘记，程序就会死锁

所以这个时候就应该使用`std::lock_guard`

这是一个模板类，传递一把锁，它会在构造的时候加锁，析构的时候解锁

```C++


void increment_counter() {  
    
    std::lock_guard<std::mutex> lock(mtx);  
      
    for (int i = 0; i < 1000; ++i) {  
        ++counter;  
    } 
} 

```

因为对象`lock`在栈上，所以离开作用域会弹出栈，自动析构


### 二、`std::recursive_mutex`相关

这是一个递归锁，主要用在递归函数中，且这个递归函数被多个线程访问

但总体来说这种编码习惯很不好，应从一开始避免这种情况发生

此处不多做介绍

### 三、`std::shared_mutex`读写锁

读写锁是一种很特殊的锁，我们假设这样一种情形。

一个报栏，读报纸的人可以有N个同时进行，但是贴报纸的人只能有一个

尽管我们可以通过`std::mutex`只让一个人读或者一个人写，但没有必要，因为**读**操作不会污染数据，**写**操作会，通过`std::shared_mutex`可以优化这种情况，实现同时读，但单个写

```C++

#include <iostream>  
#include <thread>  
#include <vector>  
#include <shared_mutex>  
#include <atomic>  
  
std::shared_mutex mtx;
std::vector<int> data;
std::atomic<bool> done{false}; 
  

void reader(int id) {  
    while (!done) {  
        mtx.lock_shared(); 
        for (const auto& value : data) {  
            std::cout << "Reader " << id << " read: " << value << std::endl;  
        }
        mtx.unlock_shared();
    }  
}  
  
void writer(int id) {  
    for (int i = 0; i < 5; ++i) {  
        mtx.lock();
        data.push_back(i);  
        std::cout << "Writer " << id << " wrote: " << i << std::endl;  
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
        mtx.unlock();
    }  
    done = true;
}  
  
int main() {  
    std::thread writer_thread(writer, 1); 
    std::vector<std::thread> reader_threads; 
  
    for (int i = 0; i < 3; ++i) {  
        reader_threads.emplace_back(reader, i);  
    }  
  
    writer_thread.join();  
    for (auto& th : reader_threads) {  
        th.join();  
    }  
  
    return 0;  
}


```
