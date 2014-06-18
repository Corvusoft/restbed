# Copyright (c) 2013, 2014 Corvusoft

project( "acceptance test suite" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( SOURCE_DIR "source" )
set( LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/test/acceptance/distribution/library" )

include( cmake/build_manifest.cmake )

#
# Build
#
add_library( helpers SHARED ${MANIFEST} )

target_link_libraries( helpers ${CMAKE_PROJECT_NAME} )
