/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/status_code.h"
#include "corvusoft/restbed/detail/status_code_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::detail::StatusCodeImpl;

//External Namespaces

namespace restbed
{
    int StatusCode::parse( const string& value )
    {
        return StatusCodeImpl::parse( value );
    }
    
    string StatusCode::to_string( const int code )
    {
        return StatusCodeImpl::to_string( code );
    }
    
    map< int, string > StatusCode::get_mappings( void )
    {
        return StatusCodeImpl::get_mappings( );
    }
    
    void StatusCode::set_mappings( const map< int, string >& values )
    {
        StatusCodeImpl::set_mappings( values );
    }
}
