# Site: restbed.net
# Author: Ben Crowhurst
#
# Copyright (c) 2013 Restbed Core Development Team and Community Contributors
#
# This file is part of Restbed.
#
# Restbed is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Restbed is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# Lesser GNU General Public License for more details.
#
# You should have received a copy of the Lesser GNU General Public License
# along with Restbed.  If not, see <http://www.gnu.org/licenses/>.

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

#
# Documentation
#
#find_package( Doxygen )
#
#if ( DOXYGEN_FOUND )
#    configure_file( ../tools/doxygen/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY )
#
#    add_custom_target( docs ${DOXYGEN_EXECUTABLE}
#                            ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
#                       WORKING_DIRECTORY
#                            ${CMAKE_CURRENT_BINARY_DIR}
#                       COMMENT
#                            "Generating API documentation with Doxygen"
#                       VERBATIM )
#endif ( DOXYGEN_FOUND )
