# Copyright (c) 2013, 2014 Corvusoft

include(ExternalProject)

macro( build_curl_local  CURL_ROOT_DIR )

	ExternalProject_Add( curl 
						 SOURCE_DIR ${CURL_ROOT_DIR}
						 BINARY_DIR ${CURL_ROOT_DIR}/curl-build
						 INSTALL_DIR ${CURL_ROOT_DIR}/curl-install
						 INSTALL_COMMAND ""
						 )

	set( curl_LIBRARY_DIR ${CURL_ROOT_DIR}/curl-build/lib )

	if(APPLE)
		set( suffix ".dylib" )
	else()
		set( suffix ".so" )
	endif()

	set( curl_LIBRARY_PATH ${CURL_ROOT_DIR}/curl-build/lib/libcurl${suffix} )

	get_filename_component( curl_LIBRARY "${curl_LIBRARY_PATH}" NAME )

endmacro()

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
	find_path( curl_DEPENDENCY_DIR CMakeLists.txt "../../../dependency/curl" )
	find_path( curl_DEPENDENCY_INCLUDE_DIR curl/curl.h "../../../dependency/curl/include" )

	message( STATUS "DIR INCLUDE ${curl_DEPENDENCY_DIR} ${curl_DEPENDENCY_INCLUDE_DIR}" )

	if( NOT curl_DEPENDENCY_DIR OR NOT curl_DEPENDENCY_INCLUDE_DIR )
		message( FATAL_ERROR "Could not find curl." )
	else()
		message( STATUS "Found curl: ${curl_DEPENDENCY_DIR}" )
	endif()

	set( curl_INCLUDE_DIR "../../../dependency/curl/include" )

endif()
