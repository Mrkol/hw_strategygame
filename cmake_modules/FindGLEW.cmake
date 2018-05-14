# FindGLEW
# --------
#
# Find the OpenGL Extension Wrangler Library (GLEW)
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines the :prop_tgt:`IMPORTED` target ``GLEW::GLEW``,
# if GLEW has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables:
#
# ::
#
#	 GLEW_INCLUDE_DIRS - include directories for GLEW
#	 GLEW_LIBRARIES - libraries to link against GLEW
#	 GLEW_FOUND - true if GLEW has been found and can be used

file(TO_CMAKE_PATH $ENV{GLEW_ROOT} GLEW_ROOT_HINT)

find_path(
	GLEW_INCLUDE_DIR GL/glew.h
	PATHS ${GLEW_ROOT_HINT}
	PATH_SUFFIXES include
	)

if(WIN32)
	string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" Debug _cmp)
	if(_cmp)
		find_file(
			GLEW_DLL NAMES glew32d.dll
			PATHS ${GLEW_ROOT_HINT}
			PATH_SUFFIXES bin/Debug/x64 debug/bin
			)
	elseif(_cmp)
		find_file(
			GLEW_DLL NAMES glew32.dll
			PATHS ${GLEW_ROOT_HINT}
			PATH_SUFFIXES bin/Release/x64 bin
			)
	endif(_cmp)
endif(WIN32)

if(NOT GLEW_LIBRARY)
	find_library(
		GLEW_LIBRARY_RELEASE 
		NAMES GLEW glew32 glew
		PATHS ${GLEW_ROOT_HINT}
		PATH_SUFFIXES lib/Release/x64 lib
		)
	find_library(
		GLEW_LIBRARY_DEBUG
		NAMES GLEWd glew32d glewd
		PATHS ${GLEW_ROOT_HINT}
		PATH_SUFFIXES lib/Debug/x64 debug/lib
		)

	include(SelectLibraryConfigurations)
	select_library_configurations(GLEW)
endif(NOT GLEW_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GLEW
	REQUIRED_VARS GLEW_INCLUDE_DIR GLEW_LIBRARY
	)

if(GLEW_FOUND)
	set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})

	if(NOT GLEW_LIBRARIES)
		set(GLEW_LIBRARIES ${GLEW_LIBRARY})
	endif()

	if (NOT TARGET GLEW::GLEW)
		add_library(GLEW::GLEW UNKNOWN IMPORTED)
		set_target_properties(GLEW::GLEW PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GLEW_INCLUDE_DIRS}")

		if(GLEW_LIBRARY_RELEASE)
			set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(GLEW::GLEW PROPERTIES IMPORTED_LOCATION_RELEASE "${GLEW_LIBRARY_RELEASE}")
		endif()

		if(GLEW_LIBRARY_DEBUG)
			set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(GLEW::GLEW PROPERTIES IMPORTED_LOCATION_DEBUG "${GLEW_LIBRARY_DEBUG}")
		endif()

		if(NOT GLEW_LIBRARY_RELEASE AND NOT GLEW_LIBRARY_DEBUG)
			set_property(TARGET GLEW::GLEW APPEND PROPERTY IMPORTED_LOCATION "${GLEW_LIBRARY}")
		endif()
	endif()
endif()

mark_as_advanced(GLEW_INCLUDE_DIR)
