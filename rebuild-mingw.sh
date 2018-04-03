#!/bin/bash

echo "Rebuilding the whole project from scratch..."

if [ -d "./build" ]; then
	rm -Rf ./build
fi

mkdir build

cd build

cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" $@ ../

cmake --build .

cd ..
