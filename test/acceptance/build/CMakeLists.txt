# Site: restbed.corvusoft.co.uk
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

project( "Acceptance Test Suite" )

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

find_package( Boost COMPONENTS thread system regex date_time )

#
# Configuration
#
set( SOURCE_DIR "../source" )
set( SUPPORT_DIR "${SOURCE_DIR}/support" )
set( FEATURE_DIR "${SOURCE_DIR}/features" )
set( STEP_DEFINITION_DIR "${SOURCE_DIR}/step_definitions" )

set( CMAKE_INSTALL_PREFIX "../distribution" )
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_INSTALL_PREFIX}/binary"  )

set( CMAKE_CXX_COMPILER clang++ )
set( CMAKE_CXX_FLAGS "-DBOOST_ALL_DYN_LINK -Weffc++" )
set( Boost_USE_STATIC_LIBS OFF )

link_directories( "../dependency/cucumber-cpp/build/src" "../../../distribution/library/" )

include_directories( "../dependency/cucumber-cpp/include" "../../../distribution/include/" ${GTEST_INCLUDE_DIR} )

#
# Build
#
add_executable( acceptance_suite ${STEP_DEFINITION_DIR}/resource.cpp )

target_link_libraries( acceptance_suite restbed libcucumber-cpp.a ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY} )
