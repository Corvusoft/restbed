# Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.

project( "restbed" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Build Options
#
option( BUILD_SHARED   "Build shared library."              OFF )
option( BUILD_EXAMPLES "Build examples applications."       OFF )
option( BUILD_TESTS    "Build all available test suites."   OFF )
option( BUILD_SSL      "Build secure socket layer support."  ON )
option( ECDHE_SUPPORT  "Support for ECDHE-based cipher suites" OFF )

#
# Configuration
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_configuration.cmake" )

message( "   ${Blue}Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.${Reset}" )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )

find_package( asio REQUIRED )
include_directories( SYSTEM ${asio_INCLUDE} )

if ( BUILD_SSL )
    find_package( openssl REQUIRED )
    include_directories( SYSTEM ${ssl_INCLUDE} )
endif ( )

if ( ECDHE_SUPPORT )
    add_definitions(-DECDHE_SUPPORT)
endif ( ECDHE_SUPPORT )

#
# Build
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_manifest.cmake" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} ${BUILD_MANIFEST} )

if ( BUILD_SSL )
    target_link_libraries( ${PROJECT_NAME} LINK_PRIVATE ${ssl_LIBRARY} ${crypto_LIBRARY} )
else ( )
    target_link_libraries( ${PROJECT_NAME} )
endif ( )

if ( BUILD_EXAMPLES )
    find_package( pam )
    find_package( syslog )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/example" )
endif ( )

if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/unit" "unit-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/acceptance" "acceptance-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/regression" "regression-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/integration" "integration-tests" )
endif ( )

#
# Install
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
install( TARGETS ${PROJECT_NAME}
         LIBRARY DESTINATION "library"
         ARCHIVE DESTINATION "library" COMPONENT library )
