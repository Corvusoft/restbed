
include(ExternalProject)

macro( build_curl  CURL_ROOT_DIR )

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

	set( BUILD_CURL_FROM_SCRATCH TRUE )

endmacro()