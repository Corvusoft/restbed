# Copyright (c) 2013, 2014, 2015 Corvusoft

find_path( framework_BUILD CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/framework" )

if ( framework_BUILD )
    set( FRAMEWORK_FOUND TRUE )
    set( framework_INCLUDE "${CMAKE_SOURCE_DIR}/dependency/framework/distribution/include" )
    set( framework_LIBRARY "${CMAKE_SOURCE_DIR}/dependency/framework/distribution/library/${CMAKE_SHARED_LIBRARY_PREFIX}framework${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    if ( NOT framework_FIND_QUIETLY )
        message( STATUS "Found framework build: ${framework_BUILD}" )
        message( STATUS "Found framework header: ${framework_INCLUDE}" )
        message( STATUS "Found framework library: ${framework_LIBRARY}" )
    endif ( )
else ( )
    if ( framework_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate framework!" )
    endif ( )
endif ( )
