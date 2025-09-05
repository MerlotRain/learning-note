find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(Stb REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")

foreach(src ${SOURCES})
    get_filename_component(dir ${src} DIRECTORY)
    get_filename_component(dir_name ${dir} NAME)
    get_filename_component(file_name ${src} NAME_WE)
    
    set(target "${dir_name}_${file_name}")
    
    add_executable(${target} ${src} shader.h)

    target_link_libraries(${target} PRIVATE 
        OpenGL::GL
        GLEW::GLEW
        glfw)
    
    set_target_properties(${target} PROPERTIES FOLDER "opengl_example")
    target_include_directories(${target} PRIVATE ${Stb_INCLUDE_DIR})
endforeach()

file(GLOB SHADERS "shaders/*")
foreach(shader ${SHADERS})
    get_filename_component(shader_name ${shader} NAME)
    configure_file(${shader} ${CMAKE_CURRENT_BINARY_DIR}/shaders/${shader_name}
        COPYONLY)
endforeach()

file(GLOB TEXTURES "textures/*")
foreach(texture ${TEXTURES})
    get_filename_component(texture_name ${texture} NAME)
    configure_file(${texture} ${CMAKE_CURRENT_BINARY_DIR}/textures/${texture_name}
        COPYONLY)
endforeach()