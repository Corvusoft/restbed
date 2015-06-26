# Copyright (c) 2013, 2014, 2015 Corvusoft

find_library( ssl_LIBRARY ssl HINTS "${CMAKE_SOURCE_DIR}/dependency/openssl" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_library( crypto_LIBRARY crypto HINTS "${CMAKE_SOURCE_DIR}/dependency/openssl" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )

if ( ssl_LIBRARY AND crypto_LIBRARY )
    set( OPENSSL_FOUND TRUE )
    add_definitions( -DBUILD_SSL=TRUE )
    
    if ( APPLE AND BUILD_SSL )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )
    endif( )

    if ( NOT openssl_FIND_QUIETLY )
        message( STATUS "Found ssl library: ${ssl_LIBRARY}" )
        message( STATUS "Found crypto library: ${crypto_LIBRARY}" )
    endif ( )
else ( )
    if ( openssl_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate ssl!" )
        message( FATAL_ERROR "Failed to locate crypto!" )
    endif ( )
endif ( )
