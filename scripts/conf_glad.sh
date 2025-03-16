#!/bin/bash
rm -rf build/ .cache/
cmake -DCMAKE_BUILD_TYPE=Release \
-DGLFW_BUILD_WAYLAND=0 \
-S . -B build/
