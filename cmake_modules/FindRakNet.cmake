# Locate RakNet
#
# The CMake variable RAKNET_DIR can be used to point this module to where the library
# is located.
#
# This module defines:
#  RAKNET_FOUND - Set to TRUE if the system has RakNet
#  RAKNET_INCLUDE_DIRS - Set to the include directory
#  RAKNET_LIBRARIES - Set to the path of the library to link against

include(FindPackageHandleStandardArgs)

file(TO_CMAKE_PATH $ENV{RAKNET_DIR} RAKNET_DIRECTORY_HINT)

find_path(RAKNET_INCLUDE_DIR
    NAMES
    RakPeer.h
    PATHS
	include
    ${RAKNET_DIR}/include
    ${RAKNET_DIRECTORY_HINT}/include
    /usr/local/include
    /usr/include
    /sw/include
    /opt/local/include
    /opt/csw/include
    /opt/include
)

# Find the debug library
find_library(RAKNET_LIBRARY_DEBUG
    NAMES RakNetDLLd RakNetd RakNetd.so RakNetDLLd.lib RakNetd.lib
    PATHS
    ${RAKNET_DIR}/lib
    ${RAKNET_DIR}
	${RAKNET_DIRECTORY_HINT}
	${RAKNET_DIRECTORY_HINT}/lib
    ENV LD_LIBRARY_PATH
    ENV LIBRARY_PATH
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    /usr/freeware/lib64
)

# Find the optimized library
find_library(RAKNET_LIBRARY_RELEASE
    NAMES RakNet RakNetDLL RakNet.so RakNet.lib RakNetDLL.lib
    PATHS
    ${RAKNET_DIR}/lib
    ${RAKNET_DIR}
	${RAKNET_DIRECTORY_HINT}
	${RAKNET_DIRECTORY_HINT}/lib
    ENV LD_LIBRARY_PATH
    ENV LIBRARY_PATH
    /usr/local/lib
    /usr/lib
    /sw/lib
    /opt/local/lib
    /opt/csw/lib
    /opt/lib
    /usr/freeware/lib64
)

set(RAKNET_LIBRARIES
    optimized ${RAKNET_LIBRARY_RELEASE}
    debug ${RAKNET_LIBRARY_DEBUG}
	)

if (WIN32)
	find_file(
		WIN_RAKNET_DLL NAMES RakNet.dll RakNetDLL.dll
		PATHS
		${RAKNET_DIRECTORY_HINT}/bin
		${RAKNET_DIRECTORY_HINT}
		)
	mark_as_advanced(WIN_RAKNET_DLL)

    set(RAKNET_LIBRARIES ${RAKNET_LIBRARIES} ws2_32.lib) # Raknet depends on Winsock 2
	
	find_package_handle_standard_args(
		RakNet DEFAULT_MSG
		RAKNET_LIBRARIES RAKNET_INCLUDE_DIR WIN_RAKNET_DLL
		)

	set(WIN_RAKNET_DLLS ${WIN_RAKNET_DLL})
else()
	find_package_handle_standard_args(
		RakNet DEFAULT_MSG
		RAKNET_LIBRARIES RAKNET_INCLUDE_DIR
		)
endif()

mark_as_advanced(RAKNET_LIBRARY_RELEASE RAKNET_LIBRARY_DEBUG RAKNET_INCLUDE_DIR)

set(NOESIS_INCLUDE_DIRS ${NOESIS_INCLUDE_DIR})