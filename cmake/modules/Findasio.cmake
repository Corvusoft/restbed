# Copyright (c) 2013, 2014, 2015 Corvusoft

find_path( asio_INCLUDE asio.hpp HINTS "${CMAKE_SOURCE_DIR}/dependency/asio/include" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( asio_INCLUDE )
    set( ASIO_FOUND TRUE )

    if ( NOT asio_FIND_QUIETLY )
        message( STATUS "Found asio header: ${asio_INCLUDE}" )
    endif ( )
else ( )
    if ( asio_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate asio!" )
    endif ( )
endif ( )
