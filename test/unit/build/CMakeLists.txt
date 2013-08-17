# File: CMakeLists.txt
# Site: appon.sourcemosaic.com
# Author: Ben Crowhurst
# Project: Application On (AppOn) Event Reaction System
#
# Copyright (c) 2013 AppOn Core Development Team and Community Contributors
#
# This file is part of AppOn (Application On).
#
# AppOn is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# AppOn is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with AppOn.  If not, see <http://www.gnu.org/licenses/>.

project( "Test Suites" )

cmake_minimum_required( VERSION 2.8.1 )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/Modules" )

set( DEPENDENCIES GTEST )

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

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( CMAKE_CXX_COMPILER clang++ ) #-s -O2 -flto -march=native
set( CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11 -Wall -Wextra -Weffc++ -pedantic" )

link_directories( "../../../distribution/library" )

include_directories( "../../../distribution/include" ${GTEST_INCLUDE_DIR} )

#
# Build
#
add_executable( method_suite ${SOURCE_DIR}/method_suite.cpp )

target_link_libraries( method_suite restbed ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} )

