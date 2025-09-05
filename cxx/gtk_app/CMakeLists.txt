pkg_check_modules(GTK4 REQUIRED IMPORTED_TARGET gtk4)

add_executable(gtk_app main.cpp)

list(REMOVE_DUPLICATES GTK4_LIBRARIES)
target_include_directories(gtk_app PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_directories(gtk_app PRIVATE ${GTK4_LIBRARY_DIRS})
target_link_libraries(gtk_app PRIVATE ${GTK4_LIBRARIES})