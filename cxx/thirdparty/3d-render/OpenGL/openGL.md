# OpenGL基本知识

## 一、渲染

渲染作为前端很重要的一个知识，简单地对渲染做解析就是，有一个现实中的物体，它具有显示的尺寸、显示的坐标系统。

我们要在设备上将它绘制出来。

屏幕就是我们最常见的一个设备，还有比如说纸张（地图）。

现实中那么大的物体呈现在二维的设备上，那么就需要做很多的操作，比如说

- 裁剪
- 投影
- 透视

二维的绘制中，我们常常将屏幕看作一个画布，这个画布通常是一个png格式的位图，通过一系列操作，我们将真实坐标转换成了画布的一个像素点。

这个像素点在设备内部就可见，设备外部就不可见。

综上所述，我们知道了在渲染或者说绘制的过程中有这么几个关键点：

* 真实的数据的坐标

* 一个算法，将真实坐标转换到设备坐标

* 设备的显示范围
