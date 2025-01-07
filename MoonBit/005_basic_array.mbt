fn main {
  // Define two array of Int.
  let arr1 : Array[Int] = [1, 2, 3, 4, 5]

  // Let compiler infer the type.
  let arr2 = [6, 7, 8, 9, 10]

  // Get the length of the array.
  println(arr1.length())

  // Access the element of the array.
  println(arr1[1]) 

  // We change the elements inside the array. 
  // The binding of arr1 is immutable, it still points to the same array.
  // The internal mutability of the array is defined by the standard library and 
  // is not affected by the binding.
  arr1.push(6) 
  arr1[1] = 10
  println("push and change element:")
  println(arr1)

  // Concat two arrays.
  let arr = arr1 + arr2
  println("concat two arrays:")
  println(arr)

  // We can also use the spread operator to concatenate arrays.
  let arr3 = [..arr1, 1000, 2000, ..arr2, 3000, 4000]
  println("spread arrays:")
  println(arr3)
}