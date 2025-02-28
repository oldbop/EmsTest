#!/bin/bash
rm -rf build/ .cache/
cmake -DGLFW_BUILD_WAYLAND=0 -S . -B build/
