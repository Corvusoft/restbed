cmake_minimum_required( VERSION 3.22.0 FATAL_ERROR )

project( "restbed" VERSION 5.0.0 LANGUAGES CXX )
message( "                                                              " )
message( "##############################################################" )
message( "#                                                            #" )
message( "#  Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.  #" )
message( "#                                                            #" )
message( "#  Restbed is dual-licensed requiring commerical entities    #" )
message( "#  to acquire a Corvusoft Permissive License, Contact        #" )
message( "#  sales@corvusoft.com for details.                          #" )
message( "#                                                            #" )
message( "##############################################################" )
message( "                                                              " )

#
# Build Options
#
option( BUILD_TESTS "Build unit tests." ON )
option( BUILD_SSL "Build secure socket layer support." ON )
option( BUILD_IPC "Build unix domain socket layer support." OFF )
option( BUILD_STATIC_LIBRARY "Build static library" ON )
option( BUILD_SHARED_LIBRARY "Build shared library" ON )
option( BUILD_DEVEL_PACKAGE "Build development package (including C++ header files)" ON )

#
# Configuration
#
set( CMAKE_CXX_STANDARD 23 )
set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src/corvusoft/${PROJECT_NAME}" )

if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( CMAKE_INSTALL_LIBDIR "library")
endif ( )

if ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set( CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/distribution" CACHE PATH "Install path prefix" FORCE )
endif ( )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0A00 /W4 /wd4068 /wd4702 /wd4996 /wd4265" )
endif ( )

if( NOT WIN32 )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -Wno-unknown-pragmas -Wno-deprecated-declarations -Wno-non-virtual-dtor" )
endif ( )

if ( UNIX AND NOT APPLE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
endif ( )

if ( APPLE )
    set( CMAKE_MACOSX_RPATH ON )
endif ( )

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake" )

find_package( asio REQUIRED )

if ( BUILD_SSL )
    add_definitions( "-DBUILD_SSL" )
    find_package( openssl REQUIRED )
endif ( )

if ( BUILD_IPC )
    add_definitions( "-DBUILD_IPC" )
endif ( )

if ( WIN32 )
	add_definitions( -DWIN_DLL_EXPORT )
endif ( )

#
# Build
#
file( GLOB_RECURSE MANIFEST "${SOURCE_DIR}/*.cpp" )

if ( BUILD_STATIC_LIBRARY )
    set( STATIC_LIBRARY_NAME "${PROJECT_NAME}-static" )
    add_library( ${STATIC_LIBRARY_NAME} STATIC ${MANIFEST} )
    set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD 23 )
    set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
    set_target_properties( ${STATIC_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )

    target_include_directories(${STATIC_LIBRARY_NAME} SYSTEM PUBLIC ${asio_INCLUDE} ${ssl_INCLUDE} ${INCLUDE_DIR})

    if ( BUILD_SSL )
        target_link_libraries( ${STATIC_LIBRARY_NAME} LINK_PRIVATE ${ssl_LIBRARY_STATIC} ${crypto_LIBRARY_STATIC} ${CMAKE_DL_LIBS} )
    else ( )
        target_link_libraries( ${STATIC_LIBRARY_NAME} ${CMAKE_DL_LIBS} )
    endif ( )
endif ( )

if ( BUILD_SHARED_LIBRARY )
    set( SHARED_LIBRARY_NAME "${PROJECT_NAME}-shared" )
    add_library( ${SHARED_LIBRARY_NAME} SHARED ${MANIFEST} )
    set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD 23 )
    set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
    if ( WIN32 )
        # Workaround to avoid name clash of static lib and dynamic import lib under windows.
        set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-shared" )
    else ( )
        set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
    endif ( )
    set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} )

    target_include_directories(${SHARED_LIBRARY_NAME} SYSTEM PUBLIC ${asio_INCLUDE} ${ssl_INCLUDE} ${INCLUDE_DIR})

    if ( BUILD_SSL )
        target_link_libraries( ${SHARED_LIBRARY_NAME} LINK_PRIVATE ${ssl_LIBRARY_SHARED} ${crypto_LIBRARY_SHARED} )
    else ( )
        target_link_libraries( ${SHARED_LIBRARY_NAME} )
    endif ( )
endif ( )

if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test" )
endif ( )

#
# Install
#
if ( BUILD_DEVEL_PACKAGE )
    file( GLOB ARTIFACTS "${SOURCE_DIR}/*.hpp" )
    install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )
    install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )
endif ( )

if ( BUILD_STATIC_LIBRARY )
    install( TARGETS ${STATIC_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
endif ( )

if ( BUILD_SHARED_LIBRARY )
    install( TARGETS ${SHARED_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
endif ( )
