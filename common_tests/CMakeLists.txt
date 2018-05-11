cmake_minimum_required(VERSION 3.5)

project(common_tests CXX)

file(GLOB_RECURSE SOURCES . src/*.cpp)

add_executable(common_tests ${SOURCES}) 

target_include_directories(common_tests 
	PRIVATE "./include"
	${GTEST_INCLUDE_DIRS}
	)

target_link_libraries(common_tests common)

target_link_libraries(common_tests
	debug ${GTEST_LIBRARY_DEBUG}
	optimized ${GTEST_LIBRARY}
	)

if(WIN32)
	target_add_dll(
		TARGET common_tests
		DLLS
		${PROTOBUF_DLL}
		${GTEST_DLL}
		)
endif(WIN32)


add_test(CommonTestsAll ${CMAKE_CURRENT_BINARY_DIR}/common_tests)
