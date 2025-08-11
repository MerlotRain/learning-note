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


    handlers/time_handler.h
    handlers/root_handler.h
    handlers/time_handler.cpp
    handlers/root_handler.cpp
    handlers/start_version_handler.h
    handlers/start_version_handler.cpp

    handlers/job/start_mapping_task_handler.h
    handlers/job/start_mapping_task_handler.cpp
    handlers/job/check_task_handler.h
    handlers/job/check_task_handler.cpp

    handlers/job/multi_resful_handler.h
    handlers/job/multi_resful_handler.cpp
)

target_include_directories(asio-demo PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(asio-demo ${Boost_LIBRARIES} gflags::gflags)