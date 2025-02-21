#!/bin/bash
rm -rf build/ .cache/
cmake -DCMAKE_C_COMPILER=clang \
-DCMAKE_CXX_COMPILER=clang++ \
-DCMAKE_BUILD_TYPE=Release \
-DGLFW_BUILD_WAYLAND=0 \
-DSYS_GL_HEADERS=yes \
-S . -B build/
