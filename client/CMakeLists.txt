cmake_minimum_required(VERSION 3.5)

project(client CXX)


file(GLOB_RECURSE SOURCES . src/*.cpp)

file(GLOB_RECURSE RESOURCES_XAML . resources/*.xaml)

add_executable(client
	${SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/client_resources.cpp
	)

generate_embeded_resources(
	OUTPUT client_resources.cpp
	RESOURCES
	${RESOURCES_XAML}
	)


if(WIN32)
	target_add_dll(
		TARGET editor
		DLLS
		${WIN_NOESIS_DLLS}
		${WIN_NOESISAPP_DLLS}
		${PROTOBUF_DLL}
		${SDL2_DLL}
		)
endif(WIN32)

target_link_libraries(
	editor
	common
	common_graphics
	)

target_include_directories(editor PUBLIC "./include")
target_include_directories(editor PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
