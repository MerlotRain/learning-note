// 说到所有权这个概念，我们就还是要回到最开始的安全性问题
// c++为什么不安全，先搞懂这个理念
// 不安全主要体现在double free, 线程数据等
// 智能指针的出现也是为了解决这个问题，本质来说，就是确定数据被谁持有，持有的数据称为引用计数
// 当引用计数为0时，则代表内存无人使用，析构
// 关于智能指针怎么设计，可以参考c++部分的内容

// 除了std::shared_ptr，之外，还有std::unique_ptr,这个类用于保证永远只有一个人持有，通常我们在app单例中使用

// rust的处理就类似与std::unque_ptr
/*
class Buffer {
public:
  Buffer() {
    data = (int *)malloc(sizeof(int) * 100);
    memset(data, 0, sizeof(int) * 100);
    for (int i = 0; i < 100; ++i) {
      data[i] = i;
    }
  }
  int *data;
};

int main() {
  std::unique_ptr<Buffer> buf(new Buffer());
  std::unique_ptr<Buffer> buf2 = std::move(buf);
  for (int i = 0; i < 100; ++i) {
    printf("%d ", buf->data[i]); // 崩溃，因为buf已经失效
  }
  return 0;
}
*/

 // 所有权其实和这个是一样的，就好比对每个值（除了基础数据类型（大小固定可以拷贝））外，都包了一层
 // std::unique_ptr，所有赋值都是std::move一样

 fn own_test() {
     let s1 = "Hello world".to_string();
     let s2 = s1; // 此时报凑
     // do something for s1
 }

 fn own_test2() {
     let n1 = 5;
     let n2 = n1; // 不报错，因为i32大小固定，可以拷贝
     // do something for n1
 }

 fn own_test3() {
     let s1 = "Hello world";
     let s2 = s1; //不报错，因为字符串在静态代码区，所以只是s2指向了它，本来大家也不用修改
     // do something for s1
 }


// 深拷贝和浅拷贝
// 深拷贝就是拷贝数据，浅拷贝就是拷贝指针
// 可以这样简单理解
// 如果你是语言的开发者，你会默认什么呢，当然是浅拷贝
// 因为指针的size是固定且值简单的，同时还能保证性能
// 所以rust 只有自动浅拷贝，什么是自动浅拷贝，就是 等号（=）
// 如果需要深拷贝，就去提供clone接口
