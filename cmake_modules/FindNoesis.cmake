# - Try to find Noesis
# Once done this will define
#  NOESIS_FOUND - System has Noesis
#  NOESIS_INCLUDE_DIRS - The Noesis include directories
#  NOESIS_LIBRARIES - The libraries needed to use Noesis
#  NOESIS_DEFINITIONS - Compiler switches required for using Noesis
#  WIN_NOESIS_DLLS - Windows specific dll files

file(TO_CMAKE_PATH $ENV{NOESIS_DIR} NOESIS_DIRECTORY_HINT)

find_path(
	NOESIS_INCLUDE_DIR Noesis_pch.h
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES Include
	)

if(UNIX)
	set(LIB_FIND_SUFFIX "Bin/linux_x86_64" "Bin/linux_x86")
elseif(WIN32)
	set(LIB_FIND_SUFFIX "Lib/windows_x86_64" "Lib/windows_x86")
endif(UNIX)


find_library(
	NOESIS_LIBRARY NAMES Noesis libNoesis.so Noesis.lib
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES ${LIB_FIND_SUFFIX}
	)

unset(LIB_FIND_SUFFIX)

mark_as_advanced(
	NOESIS_DIRECTORY_HINT
	LIB_FIND_SUFFIX
	NOESIS_INCLUDE_DIR
	NOESIS_LIBRARY
	)

include(FindPackageHandleStandardArgs)

if(WIN32)
	find_file(
		WIN_NOESIS_DLL NAMES Noesis.dll
		PATHS ${NOESIS_DIRECTORY_HINT}
		PATH_SUFFIXES "Bin/windows_x86_64" "Bin/windows_x86"
		)
	mark_as_advanced(WIN_NOESIS_DLL)

	find_package_handle_standard_args(
		NOESIS DEFAULT_MSG
		NOESIS_LIBRARY NOESIS_INCLUDE_DIR WIN_NOESIS_DLL
		)
	set(WIN_NOESIS_DLLS ${WIN_NOESIS_DLL})
else(WIN32)
	find_package_handle_standard_args(
		NOESIS DEFAULT_MSG
		NOESIS_LIBRARY NOESIS_INCLUDE_DIR
		)
endif(WIN32)

set(NOESIS_LIBRARIES ${NOESIS_LIBRARY})
set(NOESIS_INCLUDE_DIRS ${NOESIS_INCLUDE_DIR})
