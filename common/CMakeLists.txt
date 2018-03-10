cmake_minimum_required(VERSION 3.5)

project(common CXX)

include(FindProtobuf)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

file(GLOB PROTO_FILES . proto/*.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

file(GLOB SOURCES . src/*.cpp)

add_library(common STATIC ${SOURCES} ${PROTO_HDRS} ${PROTO_SRCS})

target_include_directories(common PUBLIC "./include")
