cmake_minimum_required(VERSION 3.5)

project(common_graphics CXX)

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

if(NOT OPENGL_FOUND)
	message(
		FATAL_ERROR
		"Could not load OpenGL!"
		)
endif(NOT OPENGL_FOUND)

if(NOT GLEW_FOUND)
	message(
		FATAL_ERROR
		"Could not load GLEW!"
		)
endif(NOT GLEW_FOUND)

file(GLOB_RECURSE GRAPHICS_SOURCES . src/*.cpp)

file(GLOB_RECURSE GRAPHICS_RESOURCES_XAML . resources/*.xaml)
file(GLOB_RECURSE GRAPHICS_RESOURCES_TEXTURES . resources/*.png)

add_library(common_graphics
	${GRAPHICS_SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/common_light_resources.cpp
	${CMAKE_CURRENT_BINARY_DIR}/common_heavy_resources.cpp
	)

generate_embeded_resources(
	OUTPUT common_light_resources.cpp
	RESOURCES
	${GRAPHICS_RESOURCES_XAML}
	)

generate_embeded_resources(
	OUTPUT common_heavy_resources.cpp
	RESOURCES
	${CMAKE_CURRENT_LIST_DIR}/resources/OpenSans-Regular.ttf
	${GRAPHICS_RESOURCES_TEXTURES}
	)

target_link_libraries(
	common_graphics
	common
	${NOESISAPP_LIBRARIES}
	${NOESIS_LIBRARIES}
	OpenGL::GL
	OpenGL::GLU
	GLEW::GLEW
	${SDL2_LIBRARY}
	${SDL2_GPU_LIBRARIES}
	)

target_include_directories(common_graphics PUBLIC "./include")
target_include_directories(common_graphics PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(common_graphics PUBLIC ${NOESIS_INCLUDE_DIRS})
target_include_directories(common_graphics PUBLIC ${NOESISAPP_INCLUDE_DIRS})
target_include_directories(common_graphics PUBLIC ${SDL2_INCLUDE_DIR})
target_include_directories(common_graphics PUBLIC ${SDL2_GPU_INCLUDE_DIRS})
