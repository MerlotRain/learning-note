/// mbt的函数的形式
/// fn function_name(... parameter) -> return type {}

fn add(a: Int, b: Int) ->Int {
  a + b
}

/// 如果没有返回值
/// 则直接返回Unit 这个特殊值
fn none_return() -> Unit {

}

/// 带默认参数的函数，使用b~，中间必须连续，然后指定类型和默认值
fn  default_paramter(a : Int, b~: Int = 1) -> Unit {
  println(a + b)
}

/// 调用支持顺序的问题，这种写法支持了指定参数设置，它的好处在于，假如说我们需要做sql查询，此时需要传递十几个参数，那么这种写法就有效避免了参数传递错误
fn parameter_order(a~: Int, b~: Int) -> Unit {
  println("input parameter is a: \{a}, b: \{b}")
}

fn option_func(a~: Int?) -> Unit {
  println(a.or(0))
}

fn main {
  println(add(1,2))
  none_return()
  default_paramter(1)
  parameter_order(b= 12, a=4)
  option_func(a=None)
}
