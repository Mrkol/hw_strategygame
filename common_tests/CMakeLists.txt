cmake_minimum_required(VERSION 3.5)

project(common_tests CXX)

enable_testing()
find_package(GTest REQUIRED)

if (NOT GTEST_FOUND)
	message(FATAL_ERROR
		"Could not load gtest!")
endif (NOT GTEST_FOUND)

file(GLOB_RECURSE SOURCES . src/*.cpp)

add_executable(common_tests ${SOURCES}) 

target_include_directories(common_tests PUBLIC "./include")

target_link_libraries(common_tests 
	PUBLIC common GTest::GTest protobuf::libprotobuf)

if(WIN32)
	get_filename_component(Protobuf_DIR ${Protobuf_INCLUDE_DIRS} DIRECTORY)
	get_filename_component(Gtest_DIR ${GTEST_INCLUDE_DIRS} DIRECTORY)

	target_add_dll(
		TARGET common_tests
		DLLS
		${Protobuf_DIR}/bin/libprotobuf.dll
		${Gtest_DIR}/bin/gtest.dll
		)
endif(WIN32)


add_test(CommonTestsAll ${CMAKE_CURRENT_BINARY_DIR}/common_tests)
