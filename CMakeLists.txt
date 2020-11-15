cmake_minimum_required(VERSION 3.17)
project(eliminate_colorful_balls)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    link_directories(lib/x64)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    link_directories(lib/x86)
endif ()

add_executable(${PROJECT_NAME} main.cpp main.h game.cpp game.h put_image.cpp put_image.h balloon.cpp balloon.h)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)