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

file(GLOB_RECURSE SOURCES . src/*.cpp)

file(GLOB_RECURSE RESOURCES_XAML . resources/*.xaml)

add_executable(editor
	${SOURCES}
	${CMAKE_CURRENT_BINARY_DIR}/editor_resources.cpp
	)

target_embed_resources(
	TARGET_SOURCE editor_resources.cpp
	RESOURCES
	${RESOURCES_XAML}
	${CMAKE_CURRENT_LIST_DIR}/resources/DejaVuSans-ExtraLight.ttf
	)

if(WIN32)
	get_filename_component(Protobuf_DIR ${Protobuf_INCLUDE_DIRS} DIRECTORY)
	
	target_add_dll(
		TARGET editor
		DLLS
		${WIN_NOESIS_DLLS} ${WIN_NOESISAPP_DLLS}
		${Protobuf_DIR}/bin/libprotobuf.dll
		)
endif(WIN32)

target_link_libraries(
	editor
	common
	${NOESISAPP_LIBRARIES}
	${NOESIS_LIBRARIES}
	)

if(DEBUG)
	target_compile_definitions(editor 
		PUBLIC NS_MINIMUM_LOG_LEVEL=0)
endif(DEBUG)

target_include_directories(editor PUBLIC "./include")
target_include_directories(editor PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(editor PRIVATE ${NOESIS_INCLUDE_DIRS})
target_include_directories(editor PRIVATE ${NOESISAPP_INCLUDE_DIRS})
