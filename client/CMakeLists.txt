cmake_minimum_required(VERSION 3.5)

project(client CXX)

file(GLOB_RECURSE SOURCES . src/*.cpp)

add_executable(client ${SOURCES})

target_include_directories(editor PUBLIC "./include")
