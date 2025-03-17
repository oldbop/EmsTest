cmake_minimum_required(VERSION 3.22)
project(slim_lib)

add_library(slim src/mat4.c)

target_compile_options(slim PRIVATE
  $<$<COMPILE_LANG_AND_ID:C,Clang>:-std=c99;-Wall>
  $<$<COMPILE_LANG_AND_ID:CXX,Clang>:-std=c++11;-Wall>
)

target_include_directories(slim PUBLIC include/)
