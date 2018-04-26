cmake_minimum_required(VERSION 3.5)

project(common CXX)


file(GLOB_RECURSE PROTO_FILES . proto/*.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})


file(GLOB_RECURSE SOURCES . src/*.cpp)

add_library(common STATIC ${SOURCES} ${PROTO_SRCS})

target_include_directories(common PUBLIC "./include")
target_include_directories(common PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
# target_include_directories(common PUBLIC ${PROTOBUF_INCLUDE_DIRS})

target_link_libraries(common PUBLIC protobuf::libprotobuf protobuf::libprotoc)

# You won't beleive how much f*cking time I've spent trying to
# solve a linker issue due to this define missing.
target_compile_definitions(common PUBLIC PROTOBUF_USE_DLLS)
