#!/bin/bash
rm -rf build/ .cache/
cmake -DCMAKE_BUILD_TYPE=Debug \
-DGLFW_BUILD_WAYLAND=0 \
-S . -B build/
