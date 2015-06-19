# Copyright (c) 2013, 2014, 2015 Corvusoft

set( INCLUDE_DIR "${CMAKE_SOURCE_DIR}/source" )
set( SOURCE_DIR "${INCLUDE_DIR}/corvusoft/${PROJECT_NAME}" )

if ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set( CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/distribution" CACHE PATH "Install path prefix" FORCE )
endif ( )

if ( ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" )
    if ( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 4.9 )
        message( FATAL_ERROR "\nGCC version < 4.9\nYour systems default compiler is GCC. This project makes use of c++11 features present only in versions of gcc >= 4.9. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
    endif ( )
elseif( ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
    if ( ${CMAKE_CXX_COMPILER_VERSION} VERSION_LESS 3.3 )
        message( FATAL_ERROR "\nClang version < 3.3\nYour systems default compiler is clang. This project makes use of c++11 features present only in versions of clang >= 3.3. You can use a different compiler by re-running cmake with the command switch \"-D CMAKE_CXX_COMPILER=<compiler>\" " )
    else ( )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" )
    endif ( )
else ( )
    message( FATAL_ERROR "Compiler not supported")
endif ( )

if ( CMAKE_BUILD_TYPE MATCHES Debug )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0 -Wall -Wextra -Weffc++ -pedantic" )
else ( )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2 -Wall -Wextra -Weffc++ -pedantic" )
endif ( )
