# Copyright (c) 2013, 2014 Corvusoft

find_path( framework_INCLUDE framework HINTS "/usr/include" "/usr/local/include" "/opt/local/include" "${CMAKE_SOURCE_DIR}/dependency/framework/distribution/include" )
find_library( framework_LIBRARY NAMES framework HINTS "/usr/lib" "/usr/local/lib" "/opt/local/lib" "${CMAKE_SOURCE_DIR}/dependency/framework/distribution/library" )

if ( framework_INCLUDE AND framework_LIBRARY )
    set( FRAMEWORK_FOUND TRUE )

    if ( NOT FRAMEWORK_FIND_QUIETLY )
        message( STATUS "Found framework header: ${framework_INCLUDE}" )
        message( STATUS "Found framework library: ${framework_LIBRARY}" )
    endif ( )
else ( )
    if ( FRAMEWORK_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate framework!" )
    endif ( )
endif ( )
