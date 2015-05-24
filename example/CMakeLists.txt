# Copyright (c) 2013, 2014, 2015 Corvusoft

project( "examples" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/example"  )

#
# Build
#
#add_executable( pam_authentication pam_authentication/source/example.cpp )
#target_link_libraries( pam_authentication ${CMAKE_PROJECT_NAME} pam )

#add_executable( basic_authentication basic_authentication/source/example.cpp )
#target_link_libraries( basic_authentication ${CMAKE_PROJECT_NAME} )

#add_executable( custom_status_codes custom_status_codes/source/example.cpp )
#target_link_libraries( custom_status_codes ${CMAKE_PROJECT_NAME} )

#add_executable( digest_authentication digest_authentication/source/example.cpp )
#target_link_libraries( digest_authentication ${CMAKE_PROJECT_NAME} )

#add_executable( error_handling error_handling/source/example.cpp )
#target_link_libraries( error_handling ${CMAKE_PROJECT_NAME} )

#add_executable( logging logging/source/example.cpp )
#target_link_libraries( logging ${CMAKE_PROJECT_NAME} )

#add_executable( path_parameters path_parameters/source/example.cpp )
#target_link_libraries( path_parameters ${CMAKE_PROJECT_NAME} )

add_executable( publishing_resources publishing_resources/source/example.cpp )
target_link_libraries( publishing_resources ${CMAKE_PROJECT_NAME} )

#add_executable( publishing_multipath_resources publishing_multipath_resources/source/example.cpp )
#target_link_libraries( publishing_multipath_resources ${CMAKE_PROJECT_NAME} )

add_executable( resource_filtering resource_filtering/source/example.cpp )
target_link_libraries( resource_filtering ${CMAKE_PROJECT_NAME} )

#add_executable( serving_html serving_html/source/example.cpp )
#target_link_libraries( serving_html ${CMAKE_PROJECT_NAME} )

#add_executable( syslog_logging syslog_logging/source/example.cpp )
#target_link_libraries( syslog_logging ${CMAKE_PROJECT_NAME} )

#add_executable( transfer_encoding_request transfer_encoding_request/source/example.cpp )
#target_link_libraries( transfer_encoding_request ${CMAKE_PROJECT_NAME} )

#add_executable( transfer_encoding_response transfer_encoding_response/source/example.cpp )
#target_link_libraries( transfer_encoding_response ${CMAKE_PROJECT_NAME} )

#add_executable( persistent_connection persistent_connection/source/example.cpp )
#target_link_libraries( persistent_connection ${CMAKE_PROJECT_NAME} )

#
# Install
#
install( DIRECTORY ${CMAKE_SOURCE_DIR}/example/serving_html/resource/serving_html DESTINATION "${EXECUTABLE_OUTPUT_PATH}/resource" )
