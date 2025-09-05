cmake_minimum_required(VERSION 3.10)
project(vcpkg-code)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)

add_subdirectory(ftxui_example)
add_subdirectory(gtk_app)
add_subdirectory(opengl_example)
add_subdirectory(boost_asio)