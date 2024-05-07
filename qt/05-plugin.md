# QPlugin

## 一、插件介绍

插件本身来讲也是一个动态库，但与一般的动态库不同的是，它通常具有统一的规范的接口。

插件最常用的场景就是扩展框架的能力，这个能力具体根据业务决定，一个完整的插件体系通常需要这样几个部分组成。

* 插件接口

>
> 它通常定义插件的基本信息，例如`名称`，`作者`，`版本信息`等，除此之外还有一些通用的调用，例如创建UI。

* 插件管理器

>
> 插件管理器通常用于管理所有的插件，控制插件的生命周期，这是中枢作用

* 插件加载

>
> 因为本质是一个动态库，所以就正常调用动态库加载函数。

## 二、C++的插件怎么写

如果用纯C++实现一个插件，本质来说也非常简单，下面给出一个简单的实现

```c++

// plugininterface.h

class PluginInterface
{
public:
    virtual ~PluginInterface();
    virtual const std::string& name() const = 0;
    // other interface
};

class PluginImpl : public PluginInterface
{
    // do something
};

// 
extern "C" __attribute__((visibility("default"))) PluginImpl* loadPluginImpl() 
{
    return new PluginImpl();
}

```

在这个例子中，我们先定义了一个接口类`PluginInterface`，业务插件`PluginImpl`实现插件接口，再定义导出函数`loadPluginImpl`

最终在插件管理器里根据该函数符号获取插件，这样就完成了插件的加载

以这种模式开发，通常来说我们需要做以下规范：

1. 规范插件的位置，通常来说放在`plugins`文件夹下

2. 规范插件的导出接口，如果全部使用`loadPlugin`命名，那么需要和其他开发者对齐名称

3. 规范插件的加载顺序，这种其实有点奇怪，正常来说插件的地位应该相同，加载顺序不应该影响插件功能

## 三、Qt插件

在Qt开发中，Qt为我们提供了一套完整的插件体系，与其他C++框架提供的插件体系不同的是，因为`MOC`的存在，Qt可以通过简单的宏实现插件。

我们都知道，Qt拥有一组非常经典的宏`QT_ANNOTATE_CLASS`相关，这个宏是一个标记，被该族宏标记的内容将被`MOC`编译成为`moc`代码，从而实现Qt复杂的能力。

与Qt插件相关的宏为：

* `Q_PLUGIN_METADATA`

在这里我们先给出一段代码，然后逐步讲解

```c++
#include <QObject>

class PluginInterface
{
public:
    virtual ~PluginInterface() {}
    virtual const QString &name() const = 0;
};

class PluginImpl : public QObject, public PluginInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.fjdynamics.trionmodel.PluginImpl")

public:
    PluginImpl() = default;
    const QString &name() const;
};
```

我们通过阅读Qt和moc源码来逐步解释

>
> 在这个例子中，我们定义了`PluginInterface`插件接口，这是一个不继承`QObject`的普通C++类
>
> 接着我们实现了一个插件，这个类继承了`QObject`，这一点很好解释，Qt插件主要通过元对象实现，那么必然要继承`QObject`

### 3.1 Q_PLUGIN_METADATA

```c++
// qobjectdefs.h

#define Q_PLUGIN_METADATA(x) QT_ANNOTATE_CLASS(qt_plugin_metadata, x)

// 这个宏是一个标记，标记的类型是 qt_plugin_metadata
```

在`MOC`编译器识别到这个类型后，就会生成对应的插件相关代码

我们继续看moc文件中的内容

```c++
QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x24,  'o',  'r',  'g',  '.',  'f', 
    'j',  'd',  'y',  'n',  'a',  'm',  'i',  'c', 
    's',  '.',  't',  'r',  'i',  'o',  'n',  'm', 
    'o',  'd',  'e',  'l',  '.',  'P',  'l',  'u', 
    'g',  'i',  'n',  'I',  'm',  'p',  'l', 
    // "className"
    0x03,  0x6a,  'P',  'l',  'u',  'g',  'i',  'n', 
    'I',  'm',  'p',  'l', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(PluginImpl, PluginImpl)

```

1. `QT_PLUGIN_METADATA_SECTION`，这个宏是一个标记，在不同的编译器下给出不同的标识，源码如下：
```c++
#if (defined(Q_OF_ELF) || defined(Q_OS_WIN)) && (defined (Q_CC_GNU) || defined(Q_CC_CLANG))
#  define QT_PLUGIN_METADATA_SECTION \
    __attribute__ ((section (".qtmetadata"))) __attribute__((used))
#elif defined(Q_OS_MAC)
// TODO: Implement section parsing on Mac
#  define QT_PLUGIN_METADATA_SECTION \
    __attribute__ ((section ("__TEXT,qtmetadata"))) __attribute__((used))
#elif defined(Q_CC_MSVC)
// TODO: Implement section parsing for MSVC
#pragma section(".qtmetadata",read,shared)
#  define QT_PLUGIN_METADATA_SECTION \
    __declspec(allocate(".qtmetadata"))
#else
#  define QT_PLUGIN_METADATA_SECTION
#endif
```
可以先忽略

`qt_pluginMetaData`则定义了这个插件的元信息，主要是元的基本信息，例如`metadata version`,`Qt version`等。

接下来是`IID(Interface Identifier)`，接口标识，很明显，这个就是我们在`QT_PLUGIN_METADATA_SECTION`中定义的部分。

最后是`className`，代表我们的类名

这些信息就是这个插件的元信息，当然，更多的元信息可以以`json`的形式给出，具体的方式可以自行搜索，也非常简单

2. `QT_MOC_EXPORT_PLUGIN(PluginImpl, PluginImpl)`

我们先看非静态插件的情况

```c++
#  define QT_MOC_EXPORT_PLUGIN(PLUGINCLASS, PLUGINCLASSNAME)      \
            Q_EXTERN_C Q_DECL_EXPORT \
            const char *qt_plugin_query_metadata() \
            { return reinterpret_cast<const char *>(qt_pluginMetaData); } \
            Q_EXTERN_C Q_DECL_EXPORT QT_PREPEND_NAMESPACE(QObject) *qt_plugin_instance() \
            Q_PLUGIN_INSTANCE(PLUGINCLASS)

// Q_PLUGIN_INSTANCE

#define Q_PLUGIN_INSTANCE(IMPLEMENTATION) \
        { \
            static QT_PREPEND_NAMESPACE(QPointer)<QT_PREPEND_NAMESPACE(QObject)> _instance; \
            if (!_instance) {    \
                QT_PLUGIN_RESOURCE_INIT \
                _instance = new IMPLEMENTATION; \
            } \
            return _instance; \
        }

```
这段宏展开就是

```c++
extern "C" Q_DECL_EXPORT const char* qt_plugin_query_metadata()
{ return reinterpret_cast<const char *>(qt_pluginMetaData); }

extern "C" Q_DECL_EXPORT QObject* qt_plugin_instance()
{
    static QPointer<QObject> _instance;
    if(!_instance) {
        _instance = new PluginImpl;
    }
    return _instance;
}
```

这样，我们就能清晰地看到，`moc`定义了两个导出函数，一个用来获取插件元数据，一个用来插件实例

### 3.2 QPluginLoader

我们通过这种方式生成的Qt插件，使用QPluginLoader加载，因为它内部会管理这些导出函数，直接看源码

```c++
// qlibrary.cpp

QtPluginInstanceFunction QLibraryPrivate::loadPlugin()
{
    if (auto ptr = instanceFactory.loadAcquire()) {
        libraryUnloadCount.ref();
        return ptr;
    }
    if (pluginState == IsNotAPlugin)
        return nullptr;
    if (load()) {
        auto ptr = reinterpret_cast<QtPluginInstanceFunction>(resolve("qt_plugin_instance"));
        instanceFactory.storeRelease(ptr); // two threads may store the same value
        return ptr;
    }
    if (qt_debug_component())
        qWarning() << "QLibraryPrivate::loadPlugin failed on" << fileName << ":" << errorString;
    pluginState = IsNotAPlugin;
    return nullptr;
}
```

很明显，加载动态库后获取了`qt_plugin_instance`符号，而上面的展开宏也显示，这个插件对象不会重复加载。

但明显的这个不是线程安全的操作，可同样的问题，加载插件的动作放到子线程，也不是常见的操作。

