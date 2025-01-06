import QtQuick 2.0
import QtQuick.Window 2.0


// 基本的窗口就是Window，对应这QtWidgets中的QDialog

Window {
    width: 650
    height: 400
    visible: true

    Text {
        text: "Hello world!" // 显示一个文字在左上角，位置其实非常好理解，默认在左上角，这也是屏幕坐标系原点
        anchors.centerIn: parent // 添加这句话之后，就会处于窗口的中心
        /*
            这就是qml和QWidgets中非常大的不同，在Widgets中，将Label放在中间，我们需要添加Layout，但是在QML中，只需要声明anchors就可以了
            这里简化了许多操作，可以说非常的友好
        */
    }
}

/*

QML的所有元素（暂且称为元素吧）底层都是C++的类，相关的代码在qtdeclarative/src/quick/items中，我们以Text这个元素对应的C++类来举例

class QQuickText : public QQuickImplicitSizeItem
{
        QQuickImplicitSizeItem 这是一个带隐式尺寸的类，所谓隐式尺寸，就是默认推荐的尺寸，类似我们在Designer中拖拽一个控件，这个控件有一个初始的显示效果，这个就是默认给出的尺寸，但是当我们给控件设置了Width和Height后，默认的效果就没有了


    Q_OBJECT
    // 这句是 QQuickText 的写法
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged) 
    // 这句话是 QLabel 的写法
    Q_PROPERTY(QString text READ text WRITE setText)

    这两句话的区别在于，NOTIFY这个属性，我们知道，NOTIFY绑定的是信号，也就是说，qml中属性的修改绑定了信号，也就是决定了为什么qml在属性修改的瞬间会刷新到UI上去

    同时，text 这个字段也就成为了Text的属性字段了，在qml中通过给 text 绑定值或者修改值就可以更改了
};


那么为什么QQuickText这个C++类在QML中变成了Text，这个就要说 qt通过C++开发QML组件的办法了

我们需要导出一个*.qmltypes文件，在这里定义，具体的之后再说


*/