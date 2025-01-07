fn main {
  /// # 字符串
  /// 字符串是非常常见的数据类型，我们在很多场景下需要，mbt使用 utf16 这种现代语言非常常用的编码方式存储，同时支持了Unicode编码
  let str1 = "Hello MoonBit"
  println(str1) 

  /// 字符串的主要操作

  /// 1.1 格式化
  let name = "John"
  let age = 15
  let msg = "My name is \{name}, i am \{age} years old." // 使用\{}这种方式实现格式化
  println(msg)

  // 1.2 输出
  let str2 = "你好，中国I❤️🇨🇳"
  println(str2)

  for c, _ in str2 { // 这里的语法我有点不太喜欢，遍历的时候，第一个一定是index，第二个才是值，如果可以优化就好了
  // 另一个好处就是 _ 这种匹配保留了下来，👍
    println("\{c}, index is")
  }

  // 注意，这里统计的是字符的数量，不是字节

  /// !!!! 非常注意的点
  /// String是一个固定不变的字面量，也就是不可修改的值，你可以发现，所有涉及String操作的函数，最终返回的结果都是一个新String
  /// 如果你实现字符串连续操作，可以使用StringBuilder


  // trim函数，目前已经不推荐 trim_left 和 trim_right ,改为trim_start 和 trim_end，都能接受

}