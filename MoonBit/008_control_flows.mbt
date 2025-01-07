fn main {
  println(fib(10))  
  println(sum([1,2,3,4,5]))
  println(sum2([1,2,3,4,5]))
  println(sum3([1,2,3,4,5]))
}

fn fib(n : Int) -> Int {
  if n < 2 {
    n
  } else {
    fib(n - 1) + fib(n - 2)
  }
}

fn sum(arr : Array[Int]) -> Int {
  let mut result = 0
  // Loop over the array using c-style for loop 
  for i = 0; i < arr.length(); i = i + 1 {
    result = result + arr[i]
  }
  result
}

fn sum2(arr : Array[Int]) -> Int {
  let mut result = 0
  // Use for-in loop to iterate over the array
  for i in arr {
    result += i
  }
  result
}

fn sum3(arr : Array[Int]) -> Int {
  let mut result = 0
  let mut i = 0
  while true {
    // Break the loop if we reach the end of the array.
    // MoonBit also supports continue statement.
    if i == arr.length() {
      break
    }
    result += arr[i]
    i += 1
  }
  result
}


