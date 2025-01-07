
fn main {
  // Tuple is a collection of values of different types.
  let tuple = (3.14, false, [1,2,3])  
  let tuple2 : (Float, Bool, Int) = (2.1, true, 20)
  println(tuple)
  println(tuple2)

  // Accessing tuple elements
  println(tuple.0)
  println(tuple.2)

  // Tuple can also be destructured. 
  // It's a special use case of pattern matching. We will introduce pattern matching later.
  let (a, b, c) = tuple
  println("\{a}, \{b}, \{c}")
}
