# Copyright (c) 2013, 2014 Corvusoft

set( CMAKE_FIND_LIBRARY_SUFFIXES ".a" )

find_path( GTEST_INCLUDE_DIR gtest/gtest.h "/usr/include" "/usr/local/include" )

find_library( GTEST_LIBRARY NAMES gtest PATHS "/usr/lib" "/usr/local/lib" ) 

find_library( GTEST_MAIN_LIBRARY gtest_main PATHS "/usr/lib" "/usr/local/lib" ) 

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
	    	message(FATAL_ERROR "Could not find gtest library file!")
		endif ( NOT GTEST_LIBRARY )

		if ( NOT GTEST_MAIN_LIBRARY )
	    	message(FATAL_ERROR "Could not find gtest_main library file!")
		endif ( NOT GTEST_MAIN_LIBRARY )
    endif ( GTEST_FIND_REQUIRED )
endif ( GTEST_FOUND )
