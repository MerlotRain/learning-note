
find_package(ftxui CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "*.cpp")

foreach(src ${SOURCES})
    get_filename_component(dir ${src} DIRECTORY)
    get_filename_component(dir_name ${dir} NAME)
    get_filename_component(file_name ${src} NAME_WE)
    
    set(target "${dir_name}_${file_name}")
    
    add_executable(${target} ${src})

    target_link_libraries(${target} PRIVATE 
        ftxui::component 
        ftxui::dom 
        ftxui::screen)

    set_target_properties(${target} PROPERTIES FOLDER "ftxui_example")
endforeach()