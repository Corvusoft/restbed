# Copyright (c) 2013, 2014 Corvusoft

project( "Restbed" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES asio )

foreach( DEPENDENCY ${DEPENDENCIES} )
    find_package( ${DEPENDENCY} REQUIRED )

    if ( ${DEPENDENCY}_NOTFOUND )
        message( "Failed to find dependency: " ${DEPENDENCY} )
    else( )
    	include_directories( ${ASIO_INCLUDE_DIR} )
    endif ( ${DEPENDENCY}_NOTFOUND )
endforeach( DEPENDENCY )

#
# Configuration
#
set( SOURCE_DIR "../source" )
set( FRAMEWORK_SOURCE_DIR ${SOURCE_DIR}/corvusoft/restbed )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( LIBRARY_OUTPUT_PATH    "${CMAKE_INSTALL_PREFIX}/library" )

# Check the compiler version and set flags.
if( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )

	if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.9 )
		message( FATAL_ERROR "\nGCC version < 4.9\nYour systems default compiler is GCC. This project makes use of c++11 features present only in versions of gcc >= 4.9. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
	else()
		set( CMAKE_CXX_FLAGS "" )
	endif()

elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )

	if( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.3 )
		message( FATAL_ERROR "\nClang version < 3.3\nYour systems default compiler is clang. This project makes use of c++11 features present only in versions of clang >= 3.3. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
	else()
		set( CMAKE_CXX_FLAGS "-stdlib=libc++" )
	endif()

else()
	
	message( FATAL_ERROR "Compiler not supported")

endif()

if( CMAKE_BUILD_TYPE MATCHES Debug )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra -Weffc++ -pedantic" )
else( )
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

#
# Build
#
include( build_manifest.cmake )

include_directories( ${SOURCE_DIR} )

add_library( restbed SHARED ${MANIFEST} )

target_link_libraries( restbed pthread )

#
# Install
#
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/library" )
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/include/corvusoft" )

include( build_artifacts.cmake )

install( FILES ${SOURCE_DIR}/restbed DESTINATION "include/" )
install( FILES ${FRAMEWORK_ARTIFACTS} DESTINATION "include/corvusoft/restbed" )
