cmake_minimum_required(VERSION 3.13.4)
project(div LANGUAGES C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -O2 -std=c99")

if (NOT DEFINED DIV_C)
    set(DIV_C src/div.c)
endif()

add_executable(div ${DIV_C} src/main.c)
target_include_directories(div PUBLIC include)
