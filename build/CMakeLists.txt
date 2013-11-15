# Copyright (c) 2013 Corvusoft

project( "Restbed" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES asio )

foreach( DEPENDENCY ${DEPENDENCIES} )
    find_package( ${DEPENDENCY} )

    if ( ${DEPENDENCY}_NOTFOUND )
        message( "Failed to find dependency: " ${DEPENDENCY} )
    endif ( ${DEPENDENCY}_NOTFOUND )
endforeach( DEPENDENCY )

#
# Configuration
#
set( SOURCE_DIR "../source/corvusoft" )
set( FRAMEWORK_SOURCE_DIR ${SOURCE_DIR}/restbed )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( LIBRARY_OUTPUT_PATH    "${CMAKE_INSTALL_PREFIX}/library" )

set( CMAKE_CXX_COMPILER clang++ )
set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" ) #-Wl,-install_name,libframework.dylib

#
# Build
#
include( build_manifest.cmake )

include_directories( ${SOURCE_DIR} )

add_library( restbed SHARED ${MANIFEST} )

target_link_libraries( restbed pthread )

include_directories( ${SOURCE_DIR} "../source" )
add_executable( main ../source/main.cpp )

target_link_libraries( main restbed )

#
# Install
#
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/library" )
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/include" )
file( MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/documentation" )

include( build_artifacts.cmake )

install( FILES ${FRAMEWORK_ARTIFACTS} DESTINATION "include/restbed" )
