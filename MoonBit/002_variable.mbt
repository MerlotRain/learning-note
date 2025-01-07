fn main {
  /// mbt的变量表示统一使用let定义，不支持var,这一点和rust一致，let表示不可变，let mut 表示可变，个人感觉这种处理更符合现代语言的语法设计

  /// mbt支持变量遮罩
  let var_1 = "12"
  let var_1 = @strconv.parse_int?(var_1, base = 10).unwrap() //这个抽象的语法我们后续再解释 //但是可以明显看到var_1从开始的String变成了Int
  // 为什么需要这样操作
  // 看这样一个场景，如果我们要写一个加法运算，首先需要将用户输入的值转成数字，保存字符串需要一个变量，转成数字需要另外一个变量存储，为此需要用前缀区分（或其他方式），但是再遮罩情况下
  // 就会变得很简单，遮罩后，之前的变量类型不可用
  println(var_1)

  /// mbt 的基本数据类型包含以下几种，
  /// boolean
  let b1: Bool = false
  let b2: Bool = true
  println(b1)
  println(b2)

  // integer
  let i16: Int16 = 1
  let iu16: UInt16 = 1
  let i32: Int = 1
  let iu32: UInt = 1
  let i64: Int64 = 1
  let iu64: UInt64 = 1
  println(i32)
  println(i64)
  // 有点抽象，为什么Int16不支持输出呢，说的是目前没有实现print相关的模块，emmm，后续持续关注吧
  if i64 == 1 {
    println("i64 equal 1")
  }
  else {
    println("u64 not equal 1")
  }
  /// floating
  let f32: Float = 2.3
  let f64: Double = 22.2
  println(f32)
  println(f64)
}