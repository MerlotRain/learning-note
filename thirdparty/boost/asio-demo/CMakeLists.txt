cmake_minimum_required(VERSION 3.10)
project(asio-demo)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Boost REQUIRED COMPONENTS system json)
find_package(gflags REQUIRED)

add_executable(asio-demo

    api_handler.h
    router.h
    server.h
    session.h
    
    main.cpp
    router.cpp
    server.cpp
    session.cpp

    version_handler.h
    version_handler.cpp
)

target_include_directories(asio-demo PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(asio-demo ${Boost_LIBRARIES} gflags::gflags)