cmake_minimum_required(VERSION 3.5)

project(editor CXX)

find_package(Noesis REQUIRED)
find_package(NoesisApp REQUIRED)

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

add_embedded_resource(
	editor_embedded
	RESOURCES 
	${RESOURCES_XAML}
	${CMAKE_CURRENT_LIST_DIR}/resources/DejaVuSans-ExtraLight.ttf)

add_executable(editor ${SOURCES})

add_dependencies(editor editor_embedded)

if(WIN32)
	target_add_dll(
		TARGET editor
		DLLS ${WIN_NOESIS_DLLS} ${WIN_NOESISAPP_DLLS}
		)
endif(WIN32)

target_link_libraries(
	editor
	${NOESISAPP_LIBRARIES}
	${NOESIS_LIBRARIES}
	)

target_include_directories(editor PUBLIC "./include")
target_include_directories(editor PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(editor PRIVATE ${NOESIS_INCLUDE_DIRS})
target_include_directories(editor PRIVATE ${NOESISAPP_INCLUDE_DIRS})
