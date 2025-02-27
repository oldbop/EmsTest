cmake_minimum_required(VERSION 3.22)
project(glad_lib)

add_library(glad src/gl.c)

target_include_directories(glad PUBLIC include/)
