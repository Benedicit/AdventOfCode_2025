cmake_minimum_required(VERSION 4.0)
project(AdventOfCode_2025)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)
add_executable(AdventOfCode_2025
        main.cpp
        main.h
        day1.cpp
        day1.h
        day2.h
        day2.h
        day2.h
        day2.h
        day1.cpp
        day3.cpp
        day3.h
        day4.cpp
        day4.h)
target_compile_options(AdventOfCode_2025 PRIVATE
        -O3

)

