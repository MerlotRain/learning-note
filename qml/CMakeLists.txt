cmake_minimum_required(VERSION 3.16)

project(rtk VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# qml的基本模块包含在Qml和Quick两个部分
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(apprtk
    main.cpp
)

# 添加QML模块，URI是模块的名称，VERSION是版本号，QML_FILES是模块中的QML文件
# 这样加载的文件可以被包含在qrc:/rtk/...
# 对于C++ main函数而言，这是qml入口函数
qt_add_qml_module(apprtk
    URI rtk
    VERSION 1.0
    QML_FILES
        Main.qml
        ControlModel.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apprtk PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apprtk
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apprtk
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS apprtk
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
