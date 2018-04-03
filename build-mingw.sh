#!/bin/bash

echo Building the project...

if [ ! -d ".\build" ]; then
	mkdir ".\build"
fi

cd build

cmake -G "MinGW Makefiles" -DCMAKE_SH="CMAKE_SH-NOTFOUND" $@ ../

cmake --build .

cd ..
