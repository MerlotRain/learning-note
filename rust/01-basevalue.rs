
fn base_number_value() {
    // rust是一种强类型的语言，就好比c++，强类似，但是提供auto实现自动推导，同时通过普通的变量和const的常量来区分
    // rust也是一样的处理，甚至可以说现代语言，尤其是将变量直接标记为var，let的语言都具有这种特性，大家都这样，所以不需要推陈出新
    // 而这种强类型的现代语言主要是说，我有很多种数据类型，你可以指定具体的种类，不像JavaScript，只有一个`number`
    // 那么到底是什么样子的number，鬼知道

    let n1 = 12;
    let n2:i8 = 14;
    let n3:u8 = 19;
    let n4:i16 = 255;
    let n4_1 = 12_i8;
    // 可以看出，rust使用let实现了值和变量的绑定
    // 那么为什么是let，而不是var
    // 我们都知道，rust是以安全性著称的，也就是编译时安全，编译安全，运行超大概率安全，所以值尽可能不改变，既然值默认不改变，那么使用`let`绑定这个概念更为合理

    // n1 = 14; 编译错误，无法改变值

    let n5 = 12.3; //默认直接推到为f64，当然也取决于编译器

    // 特殊的声明
    // 谈到这个的时候，我们会想起，在c/c++中，如果你想声明float，long，可以在后面加f,L这种来标记，rust也同样支持
    let n11 = 12_i8; // 只不过我们将类型直接写到数字后面，看上去有点奇怪，看多了就好
}

fn base_boolean_value() {
    // boolean，只有true,false两种状态
    let is_book = false;
    let is_pencil: bool;    // 同样的，rust也支持先声明
    is_pencil = true;       // 再赋值
    // is_pencil = false;   // 再赋值就是修改了，肯定报错
}

fn base_string_slice_value() {
    // 字符串切片
    let s_h: &str = "Hello world";
    /*
    字符串切片的理解：
    1.字符串的数据所在位置（我们先不考虑String类型）
        数据可能在堆、栈、静态代码区
        可以类比C，如果在编码的时候，我们硬编码一个字符串，那么编译之后就在静态代码区，如果我们创建一个字符串数组，那么就在栈上，malloc先不提
    2.切片的基本性质
        1)切片不拥有数据，切片只是对数据的引用，你可以看作是std::span
        2)切片基于指针和长度，这个和std::span之前的写法更像了，大家可以看我写得std::span的使用，没有std::span的时候，处理连续内存的部分数据也是用指针和长度来玩的
        3)轻量，这是肯定的，正确的，必然的
    
    3.字符串切片
        它拥有上述的所有特点，我们可以理解为这个就是const char* str = "Hello world";它的方法就是string.h中提供的方法
    */ 
}

fn base_char_value() {
    let c = 'z';
    let z = 'ℤ';
    let g = '国';
    let heart_eyed_cat = '😻';
    // rust支持所有Unicode字符，''获取的是字符，而不是子节
}

use std::mem;

fn base_char_string() {
    // rust中，字符是字符，字节是字节
    let c = '中';
    std::mem::size_of_val(&c); 

    let s = "中国";
    s.len(); // 这个获取的是子节长度
    s.chars().count(); // 这个获取的是字符长度，2
}