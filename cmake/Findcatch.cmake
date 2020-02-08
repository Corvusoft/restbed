find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/single_include/catch2" "/usr/include/catch2/single_include" "/usr/include/catch2" "/usr/local/include/catch2/single_include" "/usr/local/include/catch2" "/opt/local/include/catch2/single_include" "/opt/local/include/catch2" )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(catch DEFAULT_MSG catch_INCLUDE)
