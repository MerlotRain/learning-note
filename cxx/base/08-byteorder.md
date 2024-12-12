```C++

struct byte_order
{
	static constexpr std::uint16_t value = 0x0102;
	static constexpr auto is_litten_endian = (value & 0xFF) == 0x02;
};

constexpr bool is_litten_endian = ByteOrder::is_litten_endian;
constexpr bool is_big_endian = !ByteOrder::is_litten_endian;

```

使用C++17之后的`constexpr`风格判断，所有判断全部在编译器完成，使用非常简洁高效

```C++

void demo()
{
  if constexpr (is_litten_endian)
  {
      std::cout << "little endian" << std::endl;
  }
  else
  {
     std::cout << "big endian" << std::endl;
  }
}
```
