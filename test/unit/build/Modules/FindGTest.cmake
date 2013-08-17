# File: FindGTest.cmake
# Site: code.google.com/p/application-on
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

find_path( GTEST_INCLUDE_DIR gtest/gtest.h "/usr/include" "/usr/local/include" )

find_library( GTEST_LIBRARY NAMES gtest PATH "/usr/lib" "/usr/local/lib" ) 

find_library( GTEST_MAIN_LIBRARY NAMES gtest_main PATH "/usr/lib" "/usr/local/lib" ) 

if ( GTEST_INCLUDE_DIR AND GTEST_LIBRARY AND GTEST_MAIN_LIBRARY )
    set( GTEST_FOUND TRUE )
endif ( GTEST_INCLUDE_DIR AND GTEST_LIBRARY AND GTEST_MAIN_LIBRARY )

if ( GTEST_FOUND )
    if ( NOT GTEST_FIND_QUIETLY )
	message( STATUS "Found gtest: ${GTEST_LIBRARY}" )
    endif ( NOT  GTEST_FIND_QUIETLY )
else ( GTEST_FOUND )
    if ( GTEST_FIND_REQUIRED )
	if ( NOT GTEST_INCLUDE_DIR )
	    message( FATAL_ERROR "Could not find gtest.h header file!" )
	endif ( NOT GTEST_INCLUDE_DIR )

	if ( NOT GTEST_LIBRARY )
	    MESSAGE(FATAL_ERROR "Could not find gtest library file!")
	endif ( NOT GTEST_LIBRARY )

	if ( NOT GTEST_MAIN_LIBRARY )
	    MESSAGE(FATAL_ERROR "Could not find gtest_main library file!")
	endif ( NOT GTEST_MAIN_LIBRARY )
    endif ( GTEST_FIND_REQUIRED )
endif ( GTEST_FOUND )
