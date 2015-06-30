# Copyright (c) 2013, 2014, 2015 Corvusoft

project( "restbed" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Build Options
#
option( BUILD_SSL "Build Secure Socket Layer Support." ON )
option( BUILD_EXAMPLES "Build examples applications." OFF )
option( BUILD_TESTS "Build all available test suites." OFF )

#
# Configuration
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_configuration.cmake" )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules" )

find_package( asio REQUIRED )
find_package( framework REQUIRED )

if ( BUILD_SSL )
    find_package( openssl REQUIRED )
endif ( )

include_directories( ${framework_INCLUDE} ${asio_INCLUDE} )

#
# Build
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_manifest.cmake" )

include_directories( ${INCLUDE_DIR} )

add_library( ${PROJECT_NAME} SHARED ${BUILD_MANIFEST} )

if ( BUILD_SSL )
    target_link_libraries( ${PROJECT_NAME} ${framework_LIBRARY} pthread ${ssl_LIBRARY} ${crypto_LIBRARY} )
else ( )
    target_link_libraries( ${PROJECT_NAME} ${framework_LIBRARY} pthread )
endif ( )

if ( BUILD_EXAMPLES )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/example" )
endif ( )

#
# Install
#
include( "${CMAKE_SOURCE_DIR}/cmake/build_artifacts.cmake" )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "include" )
install( FILES ${BUILD_ARTIFACTS} DESTINATION "include/corvusoft/${PROJECT_NAME}" )
install( FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_SHARED_LIBRARY_PREFIX}${PROJECT_NAME}${CMAKE_SHARED_LIBRARY_SUFFIX}" DESTINATION "library" )

#
# Test
#
if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/unit" "unit-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/acceptance" "acceptance-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/regression" "regression-tests" )
    add_subdirectory( "${CMAKE_SOURCE_DIR}/test/integration" "integration-tests" )
endif ( )
