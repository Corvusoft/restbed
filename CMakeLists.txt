cmake_minimum_required( VERSION 2.8.10 )

project( restbed CXX )
set( restbed_VERSION_MAJOR 4 )
set( restbed_VERSION_MINOR 6.0 )
set( restbed_VERSION ${restbed_VERSION_MAJOR}.${restbed_VERSION_MINOR} )
set( PACKAGE_VERSION ${restbed_VERSION} )
set( VERSION "${restbed_VERSION}" )

#
# Build Options
#
option( BUILD_SHARED   "Build shared library."              OFF )
option( BUILD_EXAMPLES "Build examples applications."       OFF )
option( BUILD_TESTS    "Build all available test suites."   OFF )
option( BUILD_SSL      "Build secure socket layer support."  ON )

#
# Configuration
#
include( "${PROJECT_SOURCE_DIR}/cmake/configuration.cmake" )

message( "Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved." )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules" )

find_package( asio REQUIRED )
include_directories( SYSTEM ${asio_INCLUDE} )

find_package( kashmir REQUIRED )
include_directories( SYSTEM ${kashmir_INCLUDE} )

if ( BUILD_SSL )
    find_package( openssl REQUIRED )
    include_directories( SYSTEM ${ssl_INCLUDE} )
endif ( )

#
# Build
#
file( GLOB_RECURSE MANIFEST "${SOURCE_DIR}/*.cpp" )

add_library( ${PROJECT_NAME} ${MANIFEST} )

target_include_directories( ${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} )

if ( BUILD_SHARED )
    set_target_properties( ${PROJECT_NAME} PROPERTIES SOVERSION ${restbed_VERSION_MAJOR} VERSION ${restbed_VERSION} )
endif ( )

if ( BUILD_SSL )
    target_link_libraries( ${PROJECT_NAME} LINK_PRIVATE ${ssl_LIBRARY} ${crypto_LIBRARY} )
else ( )
    target_link_libraries( ${PROJECT_NAME} )
endif ( )

if ( BUILD_EXAMPLES )
    find_package( pam )
    find_package( syslog )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/example" )
endif ( )

if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/unit" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/acceptance" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/regression" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/integration" )
endif ( )

#
# Install
#
file( GLOB ARTIFACTS "${SOURCE_DIR}/*.hpp" )

if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( CMAKE_INSTALL_LIBDIR library )
endif ( )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )
install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )
install( TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
