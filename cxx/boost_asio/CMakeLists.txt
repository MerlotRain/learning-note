find_package(Boost REQUIRED COMPONENTS system json)
find_package(gflags REQUIRED)

add_executable(asio-demo
    api_handler.h
    main.cpp
    router.cpp
    router.h
    session.cpp
    session.h

    handlers/version_handler.h
    handlers/version_handler.cpp
    handlers/task_manager/interrupt_task_handler.cpp
    handlers/task_manager/interrupt_task_handler.h
    handlers/task_manager/query_task_detail_handler.cpp
    handlers/task_manager/query_task_detail_handler.h
    handlers/task_manager/query_task_result_handler.cpp
    handlers/task_manager/query_task_result_handler.h
)

target_include_directories(asio-demo PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(asio-demo ${Boost_LIBRARIES} gflags::gflags)
set_target_properties(asio-demo PROPERTIES FOLDER "boost")