find_path( ssl_INCLUDE openssl/ssl.h HINTS "/usr/local/opt/openssl/include" "/usr/include" "/usr/local/include" "/opt/local/include" )
if ( ssl_INCLUDE )
    message( STATUS "Found OpenSSL include at: ${ssl_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate OpenSSL dependency." )
endif ( )

if ( BUILD_STATIC_LIBRARY )
    find_library( ssl_LIBRARY_STATIC libssl_static.lib libssl.a HINTS "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
    find_library( crypto_LIBRARY_STATIC libcrypto_static.lib libcrypto.a HINTS  "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )

    if ( ssl_LIBRARY_STATIC AND crypto_LIBRARY_STATIC )
        message( STATUS "Found OpenSSL library at: ${ssl_LIBRARY_STATIC}" )
        message( STATUS "Found Crypto library at: ${crypto_LIBRARY_STATIC}" )
    else ( )
        message( FATAL_ERROR "Failed to locate OpenSSL dependency." )
    endif ( )
endif ( )

if ( BUILD_SHARED_LIBRARY )
    find_library( ssl_LIBRARY_SHARED libssl.lib libssl.so libssl.dylib HINTS "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
    find_library( crypto_LIBRARY_SHARED libcrypto.lib libcrypto.so libcrypto.dylib HINTS  "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )

    if ( ssl_LIBRARY_SHARED AND crypto_LIBRARY_SHARED )
        message( STATUS "Found OpenSSL library at: ${ssl_LIBRARY_SHARED}" )
        message( STATUS "Found Crypto library at: ${crypto_LIBRARY_SHARED}" )
    else ( )
        message( FATAL_ERROR "Failed to locate OpenSSL dependency." )
    endif ( )
endif ( )

set( OPENSSL_FOUND TRUE )

if ( APPLE AND BUILD_SSL )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )
endif( )
