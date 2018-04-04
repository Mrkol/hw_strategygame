cmake_minimum_required(VERSION 3.5)

if(WIN32)
	# target_add_dll(TARGET trt DLLS [dll1 [dll2 ...]])
	function(target_add_dll)
		cmake_parse_arguments(
			PA # prefix of output variables
			"" # list of names of the boolean arguments
			"TARGET" # list of names of mono-valued arguments
			"DLLS" # list of names of multi-valued arguments (output variables are lists)
			${ARGN} # arguments of the function to parse, here we take the all original ones
			)
		foreach(dll ${PA_DLLS})
			get_filename_component(dll_name ${dll} NAME)
			add_custom_command(
				TARGET ${PA_TARGET} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${dll}
				$<TARGET_FILE_DIR:${PA_TARGET}>
				)
		endforeach(dll)
	endfunction(target_add_dll)
endif(WIN32)

# target_embed_resources(TARGET_SOURCE source RESOURCES [res1 [res2 ...]])
function(target_embed_resources)
	cmake_parse_arguments(
		PA
		""
		"TARGET_SOURCE"
		"RESOURCES"
		${ARGN}
		)

	add_custom_command(
		OUTPUT ${PA_TARGET_SOURCE}
		DEPENDS ${PA_RESOURCES}
		COMMAND
		python3 ${CMAKE_SOURCE_DIR}/embedder.py ${PA_RESOURCES} -o ${CMAKE_CURRENT_BINARY_DIR} -f ${PA_TARGET_SOURCE}
		)
endfunction(target_embed_resources)


project(strategygame CXX)

option(DEBUG "Build with debug flags" OFF)
option(WITH_TESTS "Build with tests and run them" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH}
	${CMAKE_SOURCE_DIR}/cmake_modules)

if(DEBUG)
	# The option will propogate to dependent targets due
	# to the public flag.
	set(CMAKE_BUILD_TYPE Debug)
else(DEBUG)
	set(CMAKE_BUILD_TYPE Release)
endif(DEBUG)

add_subdirectory(./common)
# add_subdirectory(./client)
add_subdirectory(./editor)


if(WITH_TESTS)
	add_subdirectory("./common_tests")
endif(WITH_TESTS)



