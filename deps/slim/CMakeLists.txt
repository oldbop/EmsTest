cmake_minimum_required(VERSION 3.22)
project(slim_lib)

add_library(slim src/mat4.c)

target_include_directories(slim PUBLIC include/)
