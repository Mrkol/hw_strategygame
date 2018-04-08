cmake_minimum_required(VERSION 3.5)

project(common_tests CXX)

enable_testing()
find_package(GTest REQUIRED)

file(GLOB_RECURSE SOURCES . src/*.cpp)

add_executable(common_tests ${SOURCES}) 

target_include_directories(common_tests PUBLIC "./include")

target_link_libraries(common_tests PUBLIC common GTest::GTest GTest::Main)


add_test(CommonTestsAll ${CMAKE_CURRENT_BINARY_DIR}/common_tests)
