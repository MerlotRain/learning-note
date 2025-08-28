add_executable(hello_triangle hello_triangle.cpp)

target_link_libraries(hello_triangle     
    OpenGL::GL
    GLEW::GLEW
    glfw)

add_executable(hello_triangle_index hello_triangle_index.cpp)

target_link_libraries(hello_triangle_index     
    OpenGL::GL
    GLEW::GLEW
    glfw)