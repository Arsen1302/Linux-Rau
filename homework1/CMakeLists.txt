cmake_minimum_required(VERSION 3.26)
project(homework1)
set(CMAKE_CXX_STANDARD 17)

add_executable(homework1 main.cpp
        iterator/filter_integer_iterator.h,
        iterator/reverse_array_iterator.h,
        iterator/circular_int_iterator.h,
)