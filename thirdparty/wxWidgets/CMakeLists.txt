cmake_minimum_required(VERSION 3.18)
project(WxWidgetsExample)

find_package(wxWidgets CONFIG REQUIRED)
 
function(string_ends_with str search)
  string(FIND "${str}" "${search}" out REVERSE)
  if(${out} EQUAL -1)
    return(false)
  endif()
  string(LENGTH "${str}" len)
  string(LENGTH "${search}" len2)
  math(EXPR out "${out}+${len2}")
  if("${out}" EQUAL "${len}")
    return(true)
  endif()
  return(false)
endfunction()

file(GLOB files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

foreach(var ${files})
    string(REGEX REPLACE ".+/(.+)\\..*" "\\1" file_name ${var})
    string(FIND ${file_name} "gui" out REVERSE)
    if(${out} EQUAL -1)
        add_executable(${file_name} ${file_name}.cpp)
        target_link_libraries(${file_name} wx::core wx::base)
    else()
        add_executable(${file_name} WIN32 ${file_name}.cpp)
        target_link_libraries(${file_name} wx::core wx::base)
    endif()
endforeach()


