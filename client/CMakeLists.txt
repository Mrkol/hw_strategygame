cmake_minimum_required(VERSION 3.5)

project(client CXX)


file(GLOB_RECURSE CLIENT_SOURCES . src/*.cpp)

file(GLOB_RECURSE RESOURCES_XAML . resources/*.xaml)

add_executable(client
	${CLIENT_SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/client_resources.cpp
	)

generate_embeded_resources(
	OUTPUT client_resources.cpp
	RESOURCES
	${RESOURCES_XAML}
	)

if(WIN32)
	target_add_dll(
		TARGET client
		DLLS
		${WIN_NOESIS_DLLS}
		${WIN_NOESISAPP_DLLS}
		${PROTOBUF_DLL}
		${GLEW_DLL}
		${SDL2_DLL}
		${SDL2_GPU_DLLS}
		)
endif(WIN32)


target_link_libraries(
	client
	common
	common_graphics
	)

target_include_directories(client PRIVATE "./include")
target_include_directories(client PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
