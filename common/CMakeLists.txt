cmake_minimum_required(VERSION 3.5)

project(common CXX)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
file(GLOB_RECURSE PROTO_FILES . proto/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

file(GLOB_RECURSE SOURCES . src/*.cpp)

add_library(common STATIC ${SOURCES} ${PROTO_SRCS})

target_include_directories(common PUBLIC "./include")
target_include_directories(common PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(common PRIVATE ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(common INTERFACE ${PROTOBUF_LIBRARIES})

