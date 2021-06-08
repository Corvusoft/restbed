//System Includes
#include <map>
#include <string>
#include <memory>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/http.hpp>
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/response.hpp>
#include <corvusoft/restbed/settings.hpp>
#include <corvusoft/restbed/ssl_settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces
using restbed::Http;
using restbed::Bytes;
using restbed::Request;
using restbed::Response;
using restbed::Settings;
using restbed::SSLSettings;

//External Namespaces

#ifdef BUILD_SSL
TEST_CASE( "validate runtime_error is not thrown when SSLSettings passed into sync", "[client]" )
{
    const auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( make_shared< SSLSettings >( ) );
    
    auto request = make_shared< Request >( );
    
    REQUIRE_NOTHROW( Http::sync( request, settings ) );
}
#else
TEST_CASE( "validate runtime_error is thrown when SSLSettings passed into sync", "[client]" )
{
    const auto settings = make_shared< Settings >( );
    settings->set_ssl_settings( make_shared< SSLSettings >( ) );
    
    auto request = make_shared< Request >( );
    
    REQUIRE_THROWS_AS( Http::sync( request, settings ), runtime_error );
}
#endif

TEST_CASE( "convert request to bytes", "[http]" )
{
    auto request = make_shared< Request >( );
    
    SECTION( "default request" )
    {
        const auto bytes = Http::to_bytes( request );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "GET / HTTP/1.1\r\n\r\n" );
    }
    
    SECTION( "modified request" )
    {
        request->set_version( 1.0 );
        request->set_method( "POST" );
        request->set_protocol( "SPDY" );
        request->set_path( "/index.html" );
        request->set_body( Bytes( { 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!' } ) );
        
        multimap< string, string > parameters
        {
            { "query", "search term" },
            { "page", "1" }
        };
        
        request->set_query_parameters( parameters );
        
        multimap< string, string > headers
        {
            { "Connection", "keep-alive" }
        };
        
        request->set_headers( headers );
        
        const auto bytes = Http::to_bytes( request );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "POST /index.html?page=1&query=search%20term HTTP/1.0\r\nConnection: keep-alive\r\n\r\nHello, World!" );
    }
}

TEST_CASE( "convert response to bytes", "[http]" )
{
    auto response = make_shared< Response >( );
    
    SECTION( "default response" )
    {
        const auto bytes = Http::to_bytes( response );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "HTTP/1.1 0 \r\n\r\n" );
    }
    
    SECTION( "modified response" )
    {
        response->set_body( Bytes( { 'a', 'b' } ) );
        response->set_version( 1.0 );
        response->set_status_code( 400 );
        response->set_protocol( "SPDY" );
        response->set_status_message( "corvusoft ltd" );
        
        multimap< string, string > headers
        {
            { "Connection", "keep-alive" }
        };
        
        response->set_headers( headers );
        
        const auto bytes = Http::to_bytes( response );
        const string data( bytes.data( ), bytes.data( ) + bytes.size( ) );
        
        REQUIRE( data == "SPDY/1.0 400 corvusoft ltd\r\nConnection: keep-alive\r\n\r\nab" );
    }
}
