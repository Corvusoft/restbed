find_library( ssl_LIBRARY_STATIC libssl.a libssl_static.lib HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_library( crypto_LIBRARY_STATIC libcrypto.a libcrypto_static.lib HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )

find_library( ssl_LIBRARY_SHARED libssl.so libssl.dylib libssl.lib HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )
find_library( crypto_LIBRARY_SHARED libcrypto.so libcrypto.dylib libcrypto.lib HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl" "/usr/local/opt/openssl/lib" "/usr/lib" "/usr/local/lib" "/opt/local/lib" )

find_path( ssl_INCLUDE openssl/ssl.h HINTS "${PROJECT_SOURCE_DIR}/dependency/openssl/include" "/usr/local/opt/openssl/include" "/usr/include" "/usr/local/include" "/opt/local/include" )

if ( ssl_LIBRARY_STATIC AND ssl_LIBRARY_SHARED AND crypto_LIBRARY_STATIC AND crypto_LIBRARY_SHARED )
    set( OPENSSL_FOUND TRUE )

    if ( APPLE AND BUILD_SSL )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations" )
    endif( )

    message( STATUS "Found OpenSSL include at: ${ssl_INCLUDE}" )
    message( STATUS "Found OpenSSL library at: ${ssl_LIBRARY_STATIC}" )
    message( STATUS "Found OpenSSL library at: ${ssl_LIBRARY_SHARED}" )
    message( STATUS "Found Crypto library at: ${crypto_LIBRARY_STATIC}" )
    message( STATUS "Found Crypto library at: ${crypto_LIBRARY_SHARED}" )
else ( )
    message( FATAL_ERROR "Failed to locate OpenSSL dependency. see restbed/dependency/openssl" )
endif ( )