find_path( catch_INCLUDE catch.hpp HINTS "/usr/include/catch2/single_include" "/usr/include/catch2" "/usr/local/include/catch2/single_include" "/usr/local/include/catch2" "/opt/local/include/catch2/single_include" "/opt/local/include/catch2" )

# If the catch library was not found, we try to use the Git subnodule dependency/catch instead.
# Note that "${PROJECT_SOURCE_DIR}/..." does not always work as find_path() hint because these paths are
# relative to the sysroot of the toolchain which could differ from / when using CMake toolchain files.
# Therefore we have to check the existence of the Git submodule with EXISTS which accepts absolute paths.
# See also: https://cmake.org/cmake/help/latest/variable/CMAKE_SYSROOT.html
if ( NOT catch_INCLUDE AND EXISTS "${PROJECT_SOURCE_DIR}/dependency/catch/single_include/catch2/catch.hpp" )
    set( catch_INCLUDE "${PROJECT_SOURCE_DIR}/dependency/catch/single_include/catch2" )
endif ( )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(catch DEFAULT_MSG catch_INCLUDE)
