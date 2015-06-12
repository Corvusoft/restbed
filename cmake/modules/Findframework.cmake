# Copyright (c) 2013, 2014, 2015 Corvusoft

find_path( framework_BUILD CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/framework" )

if ( framework_BUILD )
    set( FRAMEWORK_FOUND TRUE )
    set( framework_INCLUDE "${CMAKE_SOURCE_DIR}/distribution/include" )
    set( framework_LIBRARY "${CMAKE_SOURCE_DIR}/distribution/library/${CMAKE_SHARED_LIBRARY_PREFIX}framework${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    if ( NOT framework_FIND_QUIETLY )
        message( STATUS "Found framework: ${framework_BUILD}" )
    endif ( )
else ( )
    if ( framework_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate framework!" )
    endif ( )
endif ( )
