# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
cmake_minimum_required( VERSION 3.0.2 )

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

message( "   ${Blue}Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.${Reset}" )

#
# Build
#
include( "${PROJECT_SOURCE_DIR}/cmake/manifest.cmake" )

add_library( ${PROJECT_NAME} ${MANIFEST} )

include(GNUInstallDirs)

target_include_directories( ${PROJECT_NAME}
    PRIVATE $<BUILD_INTERFACE:${INCLUDE_DIR}>
    PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )

#
# Dependencies
#
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules" )

find_package( asio REQUIRED )
target_include_directories( ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${asio_INCLUDE}> )

find_package( kashmir REQUIRED )
target_include_directories( ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${kashmir_INCLUDE}> )

if ( BUILD_SHARED )
    set_target_properties( ${PROJECT_NAME} PROPERTIES SOVERSION ${restbed_VERSION_MAJOR} VERSION ${restbed_VERSION} )
endif ( )

if ( BUILD_SSL )
    find_package( openssl REQUIRED )
    target_include_directories( ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${ssl_INCLUDE}> )
    target_link_libraries( ${PROJECT_NAME} PUBLIC ${ssl_LIBRARY} ${crypto_LIBRARY} )
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
include( "${PROJECT_SOURCE_DIR}/cmake/artifacts.cmake" )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} )
install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )
install( TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )

include(CMakePackageConfigHelpers)
export(EXPORT ${PROJECT_NAME}Targets FILE "${CMAKE_BINARY_DIR}/CMakePackage/${PROJECT_NAME}.cmake")
configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_BINARY_DIR}/CMakePackage/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
    )
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}.cmake
    DESTINATION lib/cmake/${PROJECT_NAME}
    )
install(FILES "${CMAKE_BINARY_DIR}/CMakePackage/${PROJECT_NAME}Config.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
    COMPONENT Devel
    )
