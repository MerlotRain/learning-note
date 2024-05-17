find_package(Boost REQUIRED)

file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(var ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" file_name ${var})
    add_executable(${file_name} ${file_name}.cpp)
    target_link_libraries(${file_name} Boost::boost)
endforeach()
