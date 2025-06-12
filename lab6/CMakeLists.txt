cmake_minimum_required(VERSION 3.10)

project(MY_LOG_LIB)

set(LIBRARY_SRC list.c moving.c)

include_directories(".")

add_executable(lists_exe main.c)

option(BUILD_STATIC "Build static library" OFF)

if (BUILD_STATIC)
    message("Building STATIC library")
    add_library(MY_LOG STATIC ${LIBRARY_SRC})
    target_link_libraries(lists_exe MY_LOG)
else()
    message("Building SHARED library")
    add_library(MY_LOG SHARED ${LIBRARY_SRC})
    target_link_libraries(lists_exe MY_LOG)
endif()
