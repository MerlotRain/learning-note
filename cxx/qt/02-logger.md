# QtCore

QtCore是Qt最核心的模块，对于类似信号槽这类东西不会再赘述，主要讲述一些qt中一些似乎不常用的操作。

例如日志输出，在大工程中，我们通常会引入log4j或者自己设计日志库，但qt本身是提供了日志模块的。

再例如枚举位运算，qt也做了大量支持。

Qt的性能究竟如何。

大量的封装下，再引入`moc`机制后，`qmake`编译会生成一个`.moc`文件，是否会引起比如说效率低，程序过大的情况呢。

我个人的观点是，如果要做一个跨平台的大的专业的桌面软件，例如地理信息，点云分析，三维建模，图像处理，音视频处理等，那么使用qt绝对是正确的选择。

如果是简单的小桌面程序，可以考虑使用`wxWidget`这个开源框架，后续我也会介绍这个库并使用这个库。

闲话不多说，开始。

## qDebug

一般在开发的时候，我们都需要日志去简单调试。
```C++
void fun() {
    qDebug("Debug message");
    qInfo("Info message");
    //...
}
```

对于这类的日志输出，如果觉得qt内部输出的太多了，可以用`QT_NO_WARNING_OUTPUT`和`QT_NO_DEBUG_OUTPUT`宏实现屏蔽

```C++
// qlogging.h

#define qDebug QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).debug
#define qInfo QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).info
#define qWarning QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).warning
#define qCritical QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).critical
#define qFatal QMessageLogger(QT_MESSAGELOG_FILE, QT_MESSAGELOG_LINE, QT_MESSAGELOG_FUNC).fatal

#define QT_NO_QDEBUG_MACRO while (false) QMessageLogger().noDebug
#if defined(QT_NO_DEBUG_OUTPUT)
#  undef qDebug
#  define qDebug QT_NO_QDEBUG_MACRO
#endif
#if defined(QT_NO_INFO_OUTPUT)
#  undef qInfo
#  define qInfo QT_NO_QDEBUG_MACRO
#endif
#if defined(QT_NO_WARNING_OUTPUT)
#  undef qWarning
#  define qWarning QT_NO_QDEBUG_MACRO
#endif

```

可以看出，通过设置这两个宏，可以屏蔽掉所有的日志输出。

但是qt自身输出的日志也过于简单，或者说很多时候我们需要自己的库，所以对qDebug的改造就非常重要了。

## 源码解析

```C++
qDebug() << "Hello World";

```

这句话做了很多操作，从上面的代码可以看到，先构建了一个QMessageLogger的对象，这个对象捕获了当前的文件，行号，函数名称，然后调用对象的`debug`方法

带`()`的版本返回一个`QDebug`对象，这个对象重载了`<<`运算符，而且支持各类数据的输入，所以我们能可以随便用。

`QDebug`内部有一个结构流，结构流内部有一个`QTextStream`流，这个流用来缓存所有写入的信息。

在对象销毁会调用`qt_message_print`函数，传递日志输出的所有信息。

在`qt_message_print`函数执行时，如果正常捕获了日志输出句柄，则输出，否则输出到`stderr`中

```C++
static void qt_message_print(QtMsgType, const QMessageLogContext&, const QString& message)
{
    //...
    if(grabMessageHandler()) {
        // ...
        // 获取输出句柄
        auto oldStyle = msgHandler.loadAcquire();
        auto newStye = messageHandler.loadAcquire();
        // prefer new message handler over the old one
        if (newStye || !oldStyle) {
            (newStye ? newStye : qDefaultMessageHandler)(msgType, context, message);
        } else {
    } else {
        fprintf(stderr, "%s\n", message.toLocal8Bits().constData());
    }
}
```

## 如何自定义

* 在`main`函数中注册消息句柄`qInstallMessageHandler`

* 定义句柄函数信息 `void myMessageHandler(QtMsgType, const QMessageLogContext &, const QString &)`;

## 如何轻量自定义

与上述方法不同，轻量自定义主要是定义日志输出格式。

想想看，我们为什么要自定义，主要的目的还是获取更多的日志信息，但某种程度将，如果不需要将协程或者纤程信息输出，那么Qt提供的格式化方式已然足够

`qSetMessagePattern`

改函数就是再定义日志的输出格式

占位符	描述
%{appname}	QCoreApplication::applicationName()
%{category}	日志类别
%{file}	原文件路径
%{function}	函数
%{line}	源文件所在行
%{message}	实际的消息
%{pid}	QCoreApplication::applicationPid()
%{threadid}	当前线程的系统范围ID（如果它可以获得）
%{type}	“debug”、“warning”、“critical"或"fatal”
%{time process}	“debug”、“warning”、“critical"或"fatal”
%{time boot}	消息的时间，启动进程的秒数
%{time [format]}	消息产生时,系统时间被格式化通过把格式传递至QDateTime::toString()。如果没有指定的格式，使用Qt::ISODate。
%{backtrace [depth=N] [separator=“…”]}	很多平台不支持，暂略…

## Qt with Spdlog
```c++
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

#include <QCoreApplication>
#include <QDir>
#include <QDebug>

static void qtInstallMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    std::string logMsg = msg.toStdString();
    switch (type) {
    case QtDebugMsg:
        spdlog::debug(logMsg);
        break;
    case QtInfoMsg:
        spdlog::info(logMsg);
        break;
    case QtWarningMsg:
        spdlog::warn(logMsg);
        break;
    case QtCriticalMsg:
        spdlog::error(logMsg);
        break;
    case QtFatalMsg:
        spdlog::critical(logMsg);
        abort();
    }
};

static void initLogging()
{
    try {
        QString logDir = QDir(QCoreApplication::applicationDirPath()).filePath("logs");
        QDir().mkpath(logDir);
        auto logFile = QDir(logDir).filePath("app.log");
        auto logger = spdlog::rotating_logger_mt("app_logger", logFile.toStdString(), 1048576 * 5, 50);
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        spdlog::set_default_logger(logger);
        spdlog::set_level(spdlog::level::debug);
        spdlog::flush_on(spdlog::level::info);
    } catch (const spdlog::spdlog_ex &ex) {
        fprintf(stderr, "Log initialization failed: %s\n", ex.what());
    }
    qInstallMessageHandler(qtInstallMessageHandler);
}

int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    initLogging();
    qDebug() << "This is a Qt debug message";
    qInfo() << "This is a Qt info message";
    qWarning() << "This is a Qt warning";
    qCritical() << "This is a Qt critical error";

    return app.exec();
}
```
