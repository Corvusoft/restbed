# Copyright (c) 2013, 2014 Corvusoft

project( "Examples" )

cmake_minimum_required( VERSION 2.8.10 )

#
# Configuration
#
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/distribution/binary/example"  )

#
# Build
#
add_executable( basic_authentication basic_authentication/source/example.cpp )
target_link_libraries( basic_authentication restbed )

add_executable( custom_status_codes custom_status_codes/source/example.cpp )
target_link_libraries( custom_status_codes restbed )

add_executable( digest_authentication digest_authentication/source/example.cpp )
target_link_libraries( digest_authentication restbed )

add_executable( error_handling error_handling/source/example.cpp )
target_link_libraries( error_handling restbed )

add_executable( logging logging/source/example.cpp )
target_link_libraries( logging restbed )

add_executable( path_parameters path_parameters/source/example.cpp )
target_link_libraries( path_parameters restbed )

add_executable( publishing_resources publishing_resources/source/example.cpp )
target_link_libraries( publishing_resources restbed )

add_executable( request_filtering request_filtering/source/example.cpp )
target_link_libraries( request_filtering restbed )

add_executable( serving_html serving_html/source/example.cpp )
target_link_libraries( serving_html restbed )

add_executable( syslog_logging syslog_logging/source/example.cpp )
target_link_libraries( syslog_logging restbed )

