# Copyright (c) 2013, 2014 Corvusoft

find_path( ASIO_INCLUDE_DIR asio.hpp "/usr/include" "/usr/local/include" )

if ( ASIO_INCLUDE_DIR )

    set( ASIO_FOUND TRUE )

endif ( ASIO_INCLUDE_DIR )

if ( ASIO_FOUND )

    if ( NOT ASIO_FIND_QUIETLY )
	message( STATUS "Found asio.hpp header file: ${ASIO_INCLUDE_DIR}" )
    endif ( NOT ASIO_FIND_QUIETLY )

    set(ASIO_INCLUDE_DIRS ${ASIO_INCLUDE_DIR} )

else ( ASIO_FOUND )

    if ( ASIO_FIND_REQUIRED )
	if ( NOT ASIO_INCLUDE_DIR )
	    message( FATAL_ERROR "Could not find asio.hpp header file!" )
	endif ( NOT GPG_ERROR_INCLUDE_DIR )
    endif ( ASIO_FIND_REQUIRED )
endif ( ASIO_FOUND )
