# Copyright (c) 2013, 2014 Corvusoft

include(ExternalProject)

find_library( curl_LIBRARY_PATH NAMES curl )
find_path( curl_INCLUDE_DIR NAMES curl/curl.h )

if( curl_LIBRARY_PATH AND curl_INCLUDE_DIR )
    set( curl_FOUND TRUE )

    get_filename_component( curl_LIBRARY_DIR "${curl_LIBRARY_PATH}" PATH )
    get_filename_component( curl_LIBRARY "${curl_LIBRARY_PATH}" NAME )

    message( STATUS "Found curl: ${curl_LIBRARY} ${curl_INCLUDE_DIR}/curl/curl.h" )
else( )
    message( FATAL_ERROR "Could not find curl." )
endif ( )

