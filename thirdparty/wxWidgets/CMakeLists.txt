cmake_minimum_required(VERSION 3.18)
project(WxWidgetsExample)

find_package(wxWidgets CONFIG REQUIRED)
 
# 添加源文件  
add_executable(WxWidgetsExample WIN32  main.cpp)  
target_link_libraries(WxWidgetsExample wx::core wx::base)