cmake_minimum_required( VERSION 3.1.0 FATAL_ERROR )

project( "restbed" VERSION 4.7.0 LANGUAGES CXX )
message( "                                                              " )
message( "##############################################################" )
message( "#                                                            #" )
message( "#  Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.  #" )
message( "#                                                            #" )
message( "#  Restbed is dual-licensed requiring commerical entities    #" )
message( "#  to acquire a Corvusoft Permissive License, Contact        #" )
message( "#  sales@corvusoft.co.uk for details.                        #" )
message( "#                                                            #" )
message( "##############################################################" )
message( "                                                              " )

#
# Build Options
#
option( BUILD_TESTS    "Build unit tests."   ON )
option( BUILD_SSL      "Build secure socket layer support."  ON )

#
# Configuration
#
set( CMAKE_CXX_STANDARD 14 )
set( INCLUDE_DIR "${PROJECT_SOURCE_DIR}/source" )
set( SOURCE_DIR  "${PROJECT_SOURCE_DIR}/source/corvusoft/${PROJECT_NAME}" )

if ( NOT DEFINED CMAKE_INSTALL_LIBDIR )
    set( CMAKE_INSTALL_LIBDIR "library")
endif ( )

if ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT )
    set( CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/distribution" CACHE PATH "Install path prefix" FORCE )
endif ( )

if( ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /D_WIN32_WINNT=0x0601 /W4 /wd4068 /wd4702 /wd4996" )
endif ( )

if( NOT WIN32 )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Weffc++ -pedantic -Wno-unknown-pragmas -Wno-deprecated-declarations" )
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
    find_package( openssl REQUIRED )
endif ( )

include_directories( ${INCLUDE_DIR} SYSTEM ${asio_INCLUDE} ${ssl_INCLUDE} )

if ( WIN32 )
	add_definitions( -DWIN_DLL_EXPORT )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4251")
endif ( )

#
# Build
#
file( GLOB_RECURSE MANIFEST "${SOURCE_DIR}/*.cpp" )

set( STATIC_LIBRARY_NAME "${PROJECT_NAME}-static" )
add_library( ${STATIC_LIBRARY_NAME} STATIC ${MANIFEST} )
set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD 14 )
set_property( TARGET ${STATIC_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
set_target_properties( ${STATIC_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
	
set( SHARED_LIBRARY_NAME "${PROJECT_NAME}-shared" )
add_library( ${SHARED_LIBRARY_NAME} SHARED ${MANIFEST} )
set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD 14 )
set_property( TARGET ${SHARED_LIBRARY_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
if ( WIN32 )
	# Workaround to avoid name clash of static lib and dynamic import lib under windows.
	# Another (imho better) solution would be to use different output folders for shared and static libs ...
	set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME "${PROJECT_NAME}-shared" )
else ( )
	set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} )
endif ( )	
set_target_properties( ${SHARED_LIBRARY_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR} VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR} )

if ( BUILD_SSL )
    target_link_libraries( ${SHARED_LIBRARY_NAME} LINK_PRIVATE ${ssl_LIBRARY_SHARED} ${crypto_LIBRARY_SHARED} )
    target_link_libraries( ${STATIC_LIBRARY_NAME} LINK_PRIVATE ${ssl_LIBRARY_STATIC} ${crypto_LIBRARY_STATIC} ${CMAKE_DL_LIBS} )
else ( )
    target_link_libraries( ${SHARED_LIBRARY_NAME} )
    target_link_libraries( ${STATIC_LIBRARY_NAME} ${CMAKE_DL_LIBS} )
endif ( )

if ( BUILD_TESTS )
    find_package( catch REQUIRED )

    enable_testing( )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/unit" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/feature" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/regression" )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/test/integration" )
endif ( )

if ( BUILD_STATIC )
    set(CMAKE_INSTALL_INCLUDEDIR "include")

    target_include_directories(${STATIC_LIBRARY_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        )
endif()


#
# Install
#
file( GLOB ARTIFACTS "${SOURCE_DIR}/*.hpp" )

install( FILES "${INCLUDE_DIR}/${PROJECT_NAME}" DESTINATION "${CMAKE_INSTALL_PREFIX}/include" )
install( FILES ${ARTIFACTS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/corvusoft/${PROJECT_NAME}" )

install( TARGETS ${STATIC_LIBRARY_NAME} 
         EXPORT restbedTargets 
         LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
         ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} 
         COMPONENT library )

set(INSTALL_CONFIGDIR "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

install(EXPORT restbedTargets
        FILE restbedTargets.cmake
        NAMESPACE restbed::
        DESTINATION ${INSTALL_CONFIGDIR}
        )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/restbedConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/restbedConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/restbedConfig.cmake
        INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

## Install all the helper files
install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/restbedConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/restbedConfigVersion.cmake
        DESTINATION ${INSTALL_CONFIGDIR}
)

install( TARGETS ${STATIC_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
install( TARGETS ${SHARED_LIBRARY_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT library )
