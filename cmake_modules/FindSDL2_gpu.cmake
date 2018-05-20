# - Try to find SDL2_gpu by Jonathan Dearborn

# Once done this will be defined
#  SDL2_GPU_FOUND - System has SDL2_gpu
#  SDL2_GPU_INCLUDE_DIRS - SDL2_gpu include directories
#  SDL2_GPU_LIBRARIES - The libraries needed to use SDL2_gpu
#  SDL2_GPU_DLLS - Windows specific dll files

file(TO_CMAKE_PATH $ENV{SDL2_GPU_DIR} SDL2_GPU_DIRECTORY_HINT)

find_path(
	SDL2_GPU_INCLUDE_DIR SDL_gpu.h
	PATHS ${SDL2_GPU_DIRECTORY_HINT}
	PATH_SUFFIXES include/SDL2
	)


if(WIN32)
	string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" Debug _cmp)
	if(_cmp)
		find_file(
			SDL2_GPU_DLL NAMES SDL2_gpud.dll
			PATHS ${SDL2_GPU_DIRECTORY_HINT}
			PATH_SUFFIXES lib
			)
	elseif(_cmp)
		find_file(
			SDL2_GPU_DLL NAMES SDL2_gpu.dll
			PATHS ${SDL2_GPU_DIRECTORY_HINT}
			PATH_SUFFIXES lib
			)
	endif(_cmp)
endif(WIN32)



find_library(
	SDL2_GPU_LIBRARY_RELEASE
	NAMES SDL2_gpu SDL2_gpu.lib
	PATHS ${SDL2_GPU_DIRECTORY_HINT}
	PATH_SUFFIXES lib
	)
find_library(
	SDL2_GPU_LIBRARY_DEBUG 
	NAMES SDL2_gpud SDL2_gpud.lib
	PATHS ${SDL2_GPU_DIRECTORY_HINT}
	PATH_SUFFIXES lib
	)

include(SelectLibraryConfigurations)
select_library_configurations(SDL2_GPU)

mark_as_advanced(
	SDL2_GPU_DIRECTORY_HINT
	SDL2_GPU_INCLUDE_DIR
	SDL2_GPU_LIB_DEBUG
	SDL2_GPU_LIB_RELEASE
	)

include(FindPackageHandleStandardArgs)

if(WIN32)
	find_package_handle_standard_args(
		SDL2_GPU DEFAULT_MSG
		SDL2_GPU_LIBRARY SDL2_GPU_INCLUDE_DIR SDL2_GPU_DLL
		)
	set(WIN_NOESIS_DLLS ${WIN_NOESIS_DLL})
else(WIN32)
	find_package_handle_standard_args(
		SDL2_GPU DEFAULT_MSG
		SDL2_GPU_LIBRARY SDL2_GPU_INCLUDE_DIR
		)
endif(WIN32)

set(SDL2_GPU_LIBRARIES ${SDL2_GPU_LIBRARY})
set(SDL2_GPU_INCLUDE_DIRS ${SDL2_GPU_INCLUDE_DIR})
set(SDL2_GPU_DLLS ${SDL2_GPU_DLL})
