# QFlags

这是Qt提供的用于做枚举异或操作的核心类，非常好用

```c++

enum DisplayPartten {
    Crown = 0x01,
    Trunk = 0x02,
    Ground = 0x04,
    ID = 0x08,
};
Q_DECLARE_FLAGS(DisplayParttens, DisplayPartten)

```

上述类用于管理，森林点云数据显示，包含显示树冠、树干、地面、标签，通过组合产生不同的显示效果

我们可以以此为依据对点云显示进行调整。

```C++
// 重要接口

// 测试是否添加了这个枚举
inline bool testFlag(Enum flag) const noexcept;
// 设置这个枚举是否添加，本质是将这个枚举对应的比特位写为0或者1
inline QFlags &setFlag(Enum flag, bool on = true) noexcept;
```

需要注意的是，枚举的最大值要小于`sizeof(int)`,也就是说枚举最多只能存在32个，否则会报`static_cast`错误。