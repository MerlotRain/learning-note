import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

// Define the main window of the application，对应QMainWindow的创建
ApplicationWindow {
    id: mainWindow
    width: 800 // 设置基本的窗口大小，除此之外也有类似max,min,fixed等窗口主要的属性
    height: 600
    visible: true // 为什么不默认显示呢？感觉这个是一个非常麻烦的事情
    title: "Application with Menu and Status Bar" // 设置标题，qsTr是翻译函数，可以翻译成其他语言，后续再说

    /*
        整个ApplicationWindow分为四个部分：
        menuBar
        header
        context
        footer
        除了context外其他部分都在窗口顶部或者底部，

    */

    /*
        menuBar: 基本用于实现一个MenuBar，这个比较固定了，没什么说的，那么Ribbon是否就是重写MenuBar，看起来似乎可以这样处理
        header

        ...

        context

        ...

        footer： ToolBar，用于显示状态栏
    */

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("New")
                onTriggered: console.log("New File triggered")
            }
            MenuItem {
                text: qsTr("Open")
                onTriggered: console.log("Open File triggered")
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit()
            }
        }
        Menu {
            title: qsTr("Edit")
            MenuItem {
                text: qsTr("Undo")
                onTriggered: console.log("Undo triggered")
            }
            MenuItem {
                text: qsTr("Redo")
                onTriggered: console.log("Redo triggered")
            }
        }
        Menu {
            title: qsTr("Help")
            MenuItem {
                text: qsTr("About")
                onTriggered: console.log("About triggered")
            }
        }
    }
    header: Label {
        text: qsTr("Application Header")
    }
    footer: ToolBar {
        Text {
            text: qsTr("Ready")
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    // Main content
    ColumnLayout {
        anchors.fill: parent
        spacing: 10

        Label {
            text: qsTr("Welcome to the application!")
            font.pixelSize: 24
            horizontalAlignment: Text.AlignHCenter
            Layout.alignment: Qt.AlignCenter
        }
    }
}
