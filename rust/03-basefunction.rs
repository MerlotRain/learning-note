// 灵活？ 不灵活

/*
在c++中，try catch 似乎是一个应该常用但很少用的关键字
一方面，我们希望程序保持健壮性，try-catch是必然的，可似乎另方面，都try-catch了，这种错误直接奔溃得了
因为c++真的对throw的错误，在语法上可以不处理

这与Java等语言不同，在Java中，如果一个函数可能抛出错误，你必须try-catch，否则编译失败
zig，rust都对此做出了规定，那就是抛出错误的函数必须处理
*/

fn test_try_catch() {
   let num1: i32 = "abc".parse().expect("message error");
   let num2: i32 = "42".parse().expect("message error"); // 注意，这里的42是字符串，不是kotlin中的一切皆对象
   // c++程序员可能对这种处理觉得厌烦，如果这样，那么大概率你没有使用过std::optional管理返回值
   // 在rust中，对应的就是Result这个
}


fn test_print() {
    // 占位，比c/c++好用吧，不需要指定类型了，而且很多时候复杂类型也记不清楚
    // 没有qt好用? QString("%1,%2,%1").arg("Hello").arg("world"); // hello,world,hello
    // 因为只写了两个参数却填了三个坑，简单？ 没必要啊
    println!("{}, {}", "hello", "world");
    
    // {:?} 这个是什么
    // 提问，一个Point结构体，在c++中要打印出来，怎么实现
    // 提供std::ostream& operator<<(std::ostream& os, const Point& p); 方法
    // 同样的，rust中的这个point怎么打印呢，肯定也需要实现一个类似的方法
    // 如果没有实现，那么要打印怎么处理
    // 就需要上面的方法，直接打印结构
    
}

// 表达式和语句

// 语句有;，表达式没有，这个在ReScript中也有，基于表达式，将表达式作为返回值，超级好用