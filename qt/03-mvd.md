# MVD

Qt的数据展示的核心就是MVD模型，即Model/View/Delegate

model是数据的组织形式，它的内部存储着数据和数据相关的信息，通过抽象接口对外提供访问数据或信息的方式

view不接触数据源，它要做的就是从model中获取数据然后渲染

delegate负责协调model和view上的数据。

这样做的有一些几点好处：

* 大数据集处理时，各个组件分工明确，不至于降低效率。

* model可以映射到多个view上，换句话说，我们可以通过多种方式查看数据

* 数据变更主要仅需要改动model，不需要改变view

## Model

### QModelIndex 类

我们知道model主要用来管理数据，那么如何访问数据就成了关键，Qt提供了一个叫`QModelIndex`的类，它是模型的索引，使用索引来管理整个模型

```c++
class QModelIndex{
    //...
    private:
    //...
    int r, c;
    quintptr i;
    const QAbstractItemModel* m;
}
```

`QModelIndex`核心的内容就是`r,c`两个值，存储访问或者输入的数据在模型中的位置。

我们可以简单认为，数据模型的形式就是一棵树，即使是表也是一颗树，一颗所有数据都挂在一个虚拟父节点下的子节点集合

从一棵树的角度来看，我们就容易理解，获取数据就是树的查找，写入数据就是树的插入，所以再看这些API就不会觉得奇怪了，他们本身就是树模型操作
