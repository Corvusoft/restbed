# Copyright (c) 2013, 2014 Corvusoft

project( "Acceptance Test Suite" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#

#
# Configuration
#
set( SOURCE_DIR "../source" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( LIBRARY_OUTPUT_PATH    "${CMAKE_INSTALL_PREFIX}/library" )

set( CMAKE_CXX_COMPILER clang++ )
set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" )

include( build_manifest.cmake )

add_library( helpers SHARED ${MANIFEST} )

target_link_libraries( helpers restbed )
