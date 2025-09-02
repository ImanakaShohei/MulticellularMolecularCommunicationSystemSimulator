#!/bin/bash

cmake -S ../.. -B . -DCMAKE_BUILD_TYPE=Release
cmake --build .