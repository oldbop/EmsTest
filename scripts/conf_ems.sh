#!/bin/bash
rm -rf build/ .cache/
emcmake cmake -DCMAKE_BUILD_TYPE=Release -S . -B build/
