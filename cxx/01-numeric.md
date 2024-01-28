# 数字范围

## 整数

```c++

int main() {
    short sx = 0b1111'1111'1111'1111; // -1
    unsigned short usx = 0b1111'1111'1111'1111; // USHRT_MAX
}

```

从这段代码可以看出，有符号和无符号，在二进制位上是一致的，区别在于他们的类型不同，所以最终的值不相同

## 浮点数

```c++

float f1 = 2.0f;
double d1 = 2.0;
long double ld1 = 2.0;

```

IEEE754标准
https://codebrowser.dev/glibc/glibc/sysdeps/ieee754/ieee754.h.html

