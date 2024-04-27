# 捕获U盘事件

在开发中我们还是会遇到U盘插入和拔出的状态

目前的设计思路如下：

* 存在一个App单例，用于发送U盘拔插信号

* 定义U盘的信息结构体

* 捕获的动作放在子线程中，在程序启动的时候开启线程

* 不同平台自行实现

## MacOS

```c++

#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#include <QDebug>
#include <QThread>

class DeviceMonitorThread : public QThread {
  Q_OBJECT

public:
  DeviceMonitorThread(QObject *parent = nullptr) : QThread(parent) {}

protected:
  void run() override {
    // 设置通知端口和回调函数
    mach_port_t masterPort;
    kern_return_t kr = IOMainPort(bootstrap_port, &masterPort);
    if (kr != KERN_SUCCESS) {
      qDebug() << "IOMasterPort failed";
      return;
    }

    IONotificationPortRef gNotifyPort = IONotificationPortCreate(masterPort);

    CFMutableDictionaryRef matchingDict =
        IOServiceMatching(kIOUSBDeviceClassName);
    if (!matchingDict) {
      qDebug() << "IOServiceMatching failed";
      return;
    }

    io_iterator_t iterator;
    kr = IOServiceAddMatchingNotification(
        gNotifyPort, kIOFirstMatchNotification, matchingDict, DeviceAdded, NULL,
        &iterator);
    if (kr != KERN_SUCCESS) {
      qDebug() << "IOServiceAddMatchingNotification failed";
      return;
    }

    exec();
  }

private:
  static void DeviceAdded(void *refCon, io_iterator_t iterator) {
    qDebug() << "Device added";
  }
};

```

## Windows


## Linux


U盘事件还是使用QAbstractNativeFilter操作比较好。