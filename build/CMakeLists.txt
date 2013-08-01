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
set( SOURCE_DIR "../source" )
set( FRAMEWORK_SOURCE_DIR "${SOURCE_DIR}/restbed" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( LIBRARY_OUTPUT_PATH    "${CMAKE_INSTALL_PREFIX}/library" )

set( CMAKE_CXX_COMPILER clang++ )
set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" ) #-Wl,-install_name,libframework.dylib

#
# Build
#
include( build_manifest.cmake )

include_directories( ${SOURCE_DIR} )

#add_library( restbed SHARED ${MANIFEST} )

add_executable( restbed 
		   ${FRAMEWORK_SOURCE_DIR}/main.cpp
		   ${FRAMEWORK_SOURCE_DIR}/string.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/string_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/settings.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/settings_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/status_code.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/status_code_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/method.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/method_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/resource.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/resource_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/request.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/request_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/response.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/response_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/uri.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/uri_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/resource_matcher.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/resource_matcher_impl.cpp
		   ${FRAMEWORK_SOURCE_DIR}/service.cpp
		   ${FRAMEWORK_SOURCE_DIR}/detail/service_impl.cpp )

target_link_libraries( restbed pthread )

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
