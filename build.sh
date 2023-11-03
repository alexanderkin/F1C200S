#!/usr/bin/bash
if [ ! -d "build" ]; then
    mkdir build
fi
cd build
rm -rf *
cmake -G "Unix Makefiles" ..
make -j8
cd ..