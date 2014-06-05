# Copyright (c) 2013, 2014 Corvusoft

find_path( ASIO_INCLUDE_DIR asio.hpp PATHS "/usr/include" "/usr/local/include" "/opt/local/include" "${CMAKE_SOURCE_DIR}/dependency/asio/include")

if ( ASIO_INCLUDE_DIR )
    set( ASIO_FOUND TRUE )
endif ( )

if ( ASIO_FOUND )
    if ( NOT ASIO_FIND_QUIETLY )
        message( STATUS "Found asio.hpp header file: ${ASIO_INCLUDE_DIR}" )
    endif ( )

    set(ASIO_INCLUDE_DIRS ${ASIO_INCLUDE_DIR} )
else ( )
    if ( ASIO_FIND_REQUIRED )
        if ( NOT ASIO_INCLUDE_DIR )
            message( FATAL_ERROR "Could not find asio.hpp header file!" )
        endif ( )
    endif ( )
endif ( )

