# Copyright (c) 2013, 2014, 2015 Corvusoft

find_path( framework_SOURCE CMakeLists.txt HINTS "${CMAKE_SOURCE_DIR}/dependency/framework" )

if ( framework_SOURCE )
    set( FRAMEWORK_FOUND TRUE )
    set( framework_BUILD "${CMAKE_CURRENT_BINARY_DIR}/framework_build" )
    set( framework_DISTRIBUTION "${CMAKE_CURRENT_BINARY_DIR}/framework_build/distribution" )

    include( ExternalProject )
    ExternalProject_Add( framework SOURCE_DIR ${framework_SOURCE}
                         PREFIX framework_build
                         INSTALL_DIR ${framework_DISTRIBUTION}
                         CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${framework_DISTRIBUTION} )

    set( framework_INCLUDE "${framework_DISTRIBUTION}/include" )
    set( framework_LIBRARY "${framework_DISTRIBUTION}/library/${CMAKE_SHARED_LIBRARY_PREFIX}framework${CMAKE_SHARED_LIBRARY_SUFFIX}" )

    install( FILES ${framework_LIBRARY} DESTINATION "library" )
    install( FILES "${framework_INCLUDE}/framework" DESTINATION "include" )
    install( DIRECTORY "${framework_INCLUDE}/corvusoft/framework" DESTINATION "include/corvusoft" )

    if ( NOT framework_FIND_QUIETLY )
        message( STATUS "Found framework source: ${framework_SOURCE}" )
    endif ( )
else ( )
    if ( framework_FIND_REQUIRED )
        message( FATAL_ERROR "Failed to locate framework!" )
    endif ( )
endif ( )
