find_path( asio_INCLUDE asio.hpp HINTS "/usr/include" "/usr/local/include" "/opt/local/include" )

# If the asio library was not found, we try to use the Git subnodule dependency/asio instead.
# Note that "${PROJECT_SOURCE_DIR}/..." does not always work as find_path() hint because these paths are
# relative to the sysroot of the toolchain which could differ from / when using CMake toolchain files.
# Therefore we have to check the existence of the Git submodule with EXISTS which accepts absolute paths.
# See also: https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html
if ( NOT asio_INCLUDE AND EXISTS "${PROJECT_SOURCE_DIR}/dependency/asio/asio/include/asio.hpp" )
    set( asio_INCLUDE "${PROJECT_SOURCE_DIR}/dependency/asio/asio/include" )
endif ( )

if ( asio_INCLUDE )
    set( ASIO_FOUND TRUE )
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DASIO_STANDALONE=YES" )

    message( STATUS "Found ASIO include at: ${asio_INCLUDE}" )
else ( )
    message( FATAL_ERROR "Failed to locate ASIO dependency." )
endif ( )
