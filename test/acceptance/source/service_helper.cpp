/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <restbed>
#include "callbacks.h"
#include "test_service.h"

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Mode;
using restbed::Resource;
using restbed::Settings;

//External Namespaces

const size_t NUMBER_OF_HTTP_METHODS = 8;

extern "C"
{
    TestService* create_service( const uint16_t port )
    {
        Settings settings;
        settings.set_port( port );
        settings.set_mode( Mode::ASYNCHRONOUS );
        
        TestService* service = new TestService( settings );
        service->start( );
        
        return service;
    }
    
    TestService* create_authenticated_service( const uint16_t port )
    {
        Settings settings;
        settings.set_port( port );
        settings.set_mode( Mode::ASYNCHRONOUS );
        
        TestService* service = new TestService( settings );
        service->set_authentication_handler( &authentication_handler );
        service->start( );
        
        return service;
    }
    
    void release_service( TestService* service )
    {
        delete service;
    }
    
    const char* get_log_entry( TestService* service )
    {
        return service->get_log_entry( );
    }
    
    void suppress_resource( TestService* service )
    {
        service->suppress_resource( );
    }
    
    void publish_resource( TestService* service, const char* path, const char** methods, const char* header, const char* value )
    {
        string response_header = "";
        string response_header_value = "";
        
        if ( header not_eq nullptr and value not_eq nullptr )
        {
            response_header = header;
            response_header_value = value;
        }
        
        Resource* resource = new Resource( );
        resource->set_path( path );
        
        for ( size_t index = 0; index < NUMBER_OF_HTTP_METHODS and methods[ index ] not_eq nullptr; index++ )
        {
            resource->set_method_handler( methods[ index ], std::bind( &ok_callback_handler, std::placeholders::_1, response_header, response_header_value ) );
        }
        
        service->publish_resource( *resource );
    }
    
    void publish_json_resource( TestService* service, const char* path, const char* header, const char* filter )
    {
        Resource* resource = new Resource( );
        resource->set_path( path );
        resource->set_method_handler( "GET", &json_ok_callback_handler );
        
        if ( header not_eq nullptr and filter not_eq nullptr )
        {
            resource->set_header_filter( header, filter );
        }
        
        service->publish_resource( *resource );
    }
    
    void publish_xml_resource( TestService* service, const char* path, const char* header, const char* filter )
    {
        Resource* resource = new Resource( );
        resource->set_path( path );
        resource->set_method_handler( "GET", &xml_ok_callback_handler );
        
        if ( header not_eq nullptr and filter not_eq nullptr )
        {
            resource->set_header_filter( header, filter );
        }
        
        service->publish_resource( *resource );
    }
}
