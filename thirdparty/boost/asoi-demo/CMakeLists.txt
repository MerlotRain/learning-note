find_package(Boost REQUIRED COMPONENTS system)

add_executable(asoi-demo main.cpp

    api_handler.h
    router.h
    router.cpp
    handlers/time_handler.h
    handlers/root_handler.h
    handlers/time_handler.cpp
    handlers/root_handler.cpp
)


target_include_directories(asoi-demo PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(asoi-demo ${Boost_LIBRARIES})