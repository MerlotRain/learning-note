cmake_minimum_required(VERSION 3.18)

project(delegate)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_static_delegate test_static_delegate.cpp)

add_executable(test_class_member_delegate test_class_member_delegate.cpp)

add_executable(test_delegate_observer test_delegate_observer.cpp test_delegate_observer_main.cpp)

add_executable(test_class_static_delegate test_class_static_delegate.cpp)