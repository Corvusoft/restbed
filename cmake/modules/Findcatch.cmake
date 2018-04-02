# Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.

find_path( catch_INCLUDE catch.hpp HINTS "${PROJECT_SOURCE_DIR}/dependency/catch/include" "/usr/include" "/usr/include/catch" "/usr/include/catch2" "/usr/local/include" "/usr/local/include/catch" "/usr/local/include/catch2" "/opt/local/include" "/opt/local/include/catch" "/opt/local/include/catch2" )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(catch DEFAULT_MSG catch_INCLUDE)
