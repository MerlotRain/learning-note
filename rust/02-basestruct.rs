struct Point {
    x: f64,
    y: f64,
}

// rust中没有class的概念，使用的是struct来定义结构体
// 如上我们就定义了一个点的类型

fn point_demo() {
    // 这样我们就定义了一个点的结构，这个对象在栈上
    let p: Point = Point { x: 12.0, y: 33.0 };
    // 既然是对标c++，那么肯定得考虑一下构造函数吧
    // 如同zig一样，大家会默认init作为构造函数，rust也默认new作为构造函数，但是注意，new不是关键子
    // rust的结构体只有数据，没有方法
    // 我觉得这是一种特别nice的规定，在如今编程语言单文件化的今天，如果将数据结构，函数定义，函数实现全部一股脑写在一起，比如Java这种，真的很臃肿难以阅读，尤其是对c/c++程序员来说
    // 我们已经习惯了.h文件见到那，.c文件实现，一些private函数甚至直接写在.c
    
}

// 通过impl 来对Point 实现方法
impl Point {
    // new方法，也就是构造方法
    fn new(x:f64, y:f64)->Point {
        Point { x, y }
    }
    // 一个常规方法，第一个参数时self,使用引用，这个点我想c++很常见，能引用就引用，引用比指针安全，因为指针可以运算
    // 第二个参数也是引用 double distance(const Point& rhs); // 实际就是这种写法，c++中我们要指出const，但rust默认是const，你需要手动加的是mut
    fn distance(&self, rhs:&Point) ->f64 {
        ((self.x - rhs.x).powf(2.0) + (self.y - rhs.y).powf(2.0)).sqrt()
    }

    // 第一个参数可变
    // 我们在c++,rust中必须牢记一点，c++默认可变，rust默认不可变，不可变带来安全，可变带来风险，rust的一切安全都来自 默认的不可变 及 确定安全的可变
    fn add(&mut self, x: f64, y:f64) {
        self.x += x;
        self.y += y;
    }
}

// 可以看到，我们又给point添加了一组实现，这也是非常灵活的点，可以将实现多组处理
impl Point {
    fn dot(&mut self, rhs:&Point) {
        // do something
    }
}