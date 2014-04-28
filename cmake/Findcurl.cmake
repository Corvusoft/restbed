# Copyright (c) 2013, 2014 Corvusoft

include(ExternalProject)

find_library( curl_LIBRARY_PATH NAMES curl )

find_path( curl_INCLUDE_DIR NAMES curl/curl.h )

if( curl_LIBRARY_PATH AND curl_INCLUDE_DIR )

	set( curl_FOUND TRUE )

	get_filename_component( curl_LIBRARY_DIR "${curl_LIBRARY_PATH}" PATH )
	get_filename_component( curl_LIBRARY "${curl_LIBRARY_PATH}" NAME )

	message( STATUS "Found curl: ${curl_LIBRARY} ${curl_INCLUDE_DIR}/curl/curl.h" )

else()

	# Not found in system paths so check that git submodule has been run and inform
	# the user if not.
	find_path( curl_DEPENDENCY_DIR CMakeLists.txt "${CMAKE_SOURCE_DIR}/dependency/curl" )
	find_path( curl_DEPENDENCY_INCLUDE_DIR curl/curl.h "${CMAKE_SOURCE_DIR}/dependency/curl/include" )

	if( NOT curl_DEPENDENCY_DIR OR NOT curl_DEPENDENCY_INCLUDE_DIR )
		message( FATAL_ERROR "Could not find curl." )
	else()
		message( STATUS "Found curl: ${curl_DEPENDENCY_DIR}" )
	endif()

	set( curl_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/dependency/curl/include" )

endif()
