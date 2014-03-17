# Copyright (c) 2013, 2014 Corvusoft

project( "Publishing Resources Example" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

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
	set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -ggdb -O0 -Wall -Wextra -Weffc++ -pedantic" )
else( )
	set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )
endif( CMAKE_BUILD_TYPE MATCHES Debug )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" )

#
# Build
#
add_executable( example ${SOURCE_DIR}/example.cpp )

target_link_libraries( example restbed )
