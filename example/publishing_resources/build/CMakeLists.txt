# Copyright (c) 2013, 2014 Corvusoft

project( "Publishing Resources Example" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( CMAKE_CXX_COMPILER clang++ )

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
