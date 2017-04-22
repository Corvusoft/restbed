# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.

find_library( ssl_LIBRARY ssl ssleay32 HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl/out32dll" "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_library( crypto_LIBRARY crypto libeay32 HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl/out32dll" "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_path( ssl_INCLUDE openssl/ssl.h HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl/inc32" "${PROJECT_SOURCE_DIR}/dependency/openssl/include" "/usr/local/opt/openssl/include" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( ssl_INCLUDE AND ssl_LIBRARY AND crypto_LIBRARY )
    set( OPENSSL_FOUND TRUE )
    add_definitions( -DBUILD_SSL=TRUE )

    if ( APPLE AND BUILD_SSL )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )
    endif( )

    message( STATUS "${Green}Found OpenSSL library at: ${ssl_LIBRARY}${Reset}" )
    message( STATUS "${Green}Found OpenSSL include at: ${ssl_INCLUDE}${Reset}" )
    message( STATUS "${Green}Found Crypto library at: ${crypto_LIBRARY}${Reset}" )
else ( )
    message( FATAL_ERROR "${Red}Failed to locate OpenSSL dependency. see restbed/dependency/openssl; ./config shared; make all${Reset}" )
endif ( )
