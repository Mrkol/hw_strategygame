cmake_minimum_required(VERSION 3.5)

project(editor CXX)

if(NOT NOESIS_FOUND)
	message(
		FATAL_ERROR
		"Could not load the noesis library!"
		)
endif(NOT NOESIS_FOUND)

if(NOT NOESISAPP_FOUND)
	message(
		FATAL_ERROR
		"Could not load the noesis app framework!"
		)
endif(NOT NOESISAPP_FOUND)

if(NOT SDL2_FOUND)
	message(
		FATAL_ERROR
		"Could not load SDL2!"
		)
endif(NOT SDL2_FOUND)

file(GLOB_RECURSE SOURCES . src/*.cpp)

file(GLOB_RECURSE COMMON_RESOURCES_XAML . resources/*.xaml)

add_library(common_graphics
	${SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/common_light_resources.cpp
	${CMAKE_CURRENT_BINARY_DIR}/common_heavy_resources.cpp
	)

generate_embeded_resources(
	OUTPUT common_light_resources.cpp
	RESOURCES
	${COMMON_RESOURCES_XAML}
	${CMAKE_CURRENT_LIST_DIR}/resources/OpenSans-Regular.ttf
	)

generate_embeded_resources(
	OUTPUT common_heavy_resources.cpp
	RESOURCES
	${CMAKE_CURRENT_LIST_DIR}/resources/OpenSans-Regular.ttf
	)

target_link_libraries(
	common_graphics
	common
	${NOESISAPP_LIBRARIES}
	${NOESIS_LIBRARIES}
	${SDL2_LIBRARY}
	)

target_include_directories(editor PUBLIC "./include")
target_include_directories(editor PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(editor PUBLIC ${NOESIS_INCLUDE_DIRS})
target_include_directories(editor PUBLIC ${NOESISAPP_INCLUDE_DIRS})
target_include_directories(editor PUBLIC ${SDL2_INCLUDE_DIR})
