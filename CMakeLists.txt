cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(strategygame CXX)

option(DEBUG "Build with debug flags" OFF)
option(WITH_TESTS "Build with tests and run them" OFF)



add_subdirectory("./common")
# add_subdirectory("./client")
add_subdirectory("./editor")

if(DEBUG)
	# The option will propogate to dependent targets due
	# to the public flag.
	target_compile_options(common PUBLIC -g)
endif(DEBUG)

if(WITH_TESTS)
	add_subdirectory("./common_tests")
endif(WITH_TESTS)



