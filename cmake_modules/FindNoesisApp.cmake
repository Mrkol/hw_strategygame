# - Try to find NoesisApp
# Once done this will define
#  NOESISAPP_FOUND - System has Noesis
#  NOESISAPP_INCLUDE_DIRS - The Noesis include directories
#  NOESISAPP_LIBRARIES - The libraries needed to use NoesisApp
#  WIN_NOESISAPP_DLLS - Windows specific dll files

file(TO_CMAKE_PATH $ENV{NOESIS_DIR} NOESIS_DIRECTORY_HINT)

find_path(
	NOESISAPP_Launcher_INCLUDE_DIR NsApp/Launcher.h
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES "Include" "Src/Packages/App/Launcher/Include"
	)
find_path(
	NOESISAPP_Display_INCLUDE_DIR NsApp/Display.h
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES "Include" "Src/Packages/App/Display/Include"
	)
find_path(
	NOESISAPP_ApplicationLauncher_INCLUDE_DIR NsApp/Application.h
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES "Include" "Src/Packages/App/ApplicationLauncher/Include"
	)
find_path(
	NOESISAPP_DisplayLauncher_INCLUDE_DIR NsApp/DisplayLauncher.h
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES "Include" "Src/Packages/App/DisplayLauncher/Include"
	)

if(UNIX)
	set(LIB_FIND_SUFFIX "Bin/linux_x86_64" "Bin/linux_x86")
elseif(WIN32)
	set(LIB_FIND_SUFFIX "Lib/windows_x86_64" "Lib/windows_x86")
endif(UNIX)

find_library(
	NOESISAPP_LIBRARY NAMES NoesisApp libNoesisApp.so NoesisApp.lib 
	PATHS ${NOESIS_DIRECTORY_HINT}
	PATH_SUFFIXES ${LIB_FIND_SUFFIX}
	)

unset(LIB_FIND_SUFFIX)

mark_as_advanced(
	NOESISAPP_LIBRARY
	NOESISAPP_Launcher_INCLUDE_DIR
	NOESISAPP_Display_INCLUDE_DI
	NOESISAPP_ApplicationLauncher_INCLUDE_DI
	NOESISAPP_DisplayLauncher_INCLUDE_DIR
	)

include(FindPackageHandleStandardArgs)

if(WIN32)
	find_file(
		WIN_NOESISAPP_DLL NAMES NoesisApp.dll
		PATHS ${NOESIS_DIRECTORY_HINT}
		PATH_SUFFIXES "Bin/windows_x86_64" "Bin/windows_x86"
		)
	mark_as_advanced(WIN_NOESISAPP_DLL)

	find_package_handle_standard_args(
		NOESISAPP  DEFAULT_MSG
		NOESISAPP_LIBRARY
		NOESISAPP_Launcher_INCLUDE_DIR
		NOESISAPP_Display_INCLUDE_DIR
		NOESISAPP_ApplicationLauncher_INCLUDE_DIR
		NOESISAPP_DisplayLauncher_INCLUDE_DIR WIN_NOESISAPP_DLL
		)
	set(WIN_NOESISAPP_DLLS ${WIN_NOESISAPP_DLL})
else(WIN32)
	find_package_handle_standard_args(
		NOESISAPP  DEFAULT_MSG
		NOESISAPP_LIBRARY
		NOESISAPP_Launcher_INCLUDE_DIR
		NOESISAPP_Display_INCLUDE_DIR
		NOESISAPP_ApplicationLauncher_INCLUDE_DIR
		NOESISAPP_DisplayLauncher_INCLUDE_DIR
		)
endif(WIN32)

set(NOESISAPP_LIBRARIES
	${NOESISAPP_LIBRARY})
set(NOESISAPP_INCLUDE_DIRS
	${NOESISAPP_Launcher_INCLUDE_DIR}
	${NOESISAPP_Display_INCLUDE_DIR}
	${NOESISAPP_ApplicationLauncher_INCLUDE_DIR}
	${NOESISAPP_DisplayLauncher_INCLUDE_DIR})
