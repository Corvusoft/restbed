//System Includes
#include <map>
#include <string>
#include <chrono>

//Project Includes
#include <corvusoft/restbed/settings.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::map;
using std::string;
using std::multimap;
using std::chrono::milliseconds;

//Project Namespaces
using restbed::Settings;

//External Namespaces

TEST_CASE( "validate default instance values", "[settings]" )
{
    const Settings settings;
    
    REQUIRE( settings.get_port( ) == 80 );
    REQUIRE( settings.get_root( ) == "/" );
    REQUIRE( settings.get_worker_limit( ) == 0 );
    REQUIRE( settings.get_properties( ).empty( ) );
    REQUIRE( settings.get_bind_address( ).empty( ) );
    REQUIRE( settings.get_connection_limit( ) == 128 );
    REQUIRE( settings.get_default_headers( ).empty( ) );
    REQUIRE( settings.get_case_insensitive_uris( ) == true );
    REQUIRE( settings.get_connection_timeout( ) == milliseconds( 5000 ) );
    
    map< int, string > expectation =
    {
        { 100, "Continue" },
        { 101, "Switching Protocols" },
        { 102, "Processing" },
        { 200, "OK" },
        { 201, "Created" },
        { 202, "Accepted" },
        { 203, "Non-Authoritative Information" },
        { 204, "No Content" },
        { 205, "Reset Content" },
        { 206, "Partial Content" },
        { 207, "Multi-Status" },
        { 208, "Already Reported" },
        { 226, "IM Used" },
        { 300, "Multiple Choices" },
        { 301, "Moved Permanently" },
        { 302, "Found" },
        { 303, "See Other" },
        { 304, "Not Modified" },
        { 305, "Use Proxy" },
        { 306, "Reserved" },
        { 307, "Temporary Redirect" },
        { 308, "Permanent Redirect" },
        { 400, "Bad Request" },
        { 401, "Unauthorized" },
        { 402, "Payment Required" },
        { 403, "Forbidden" },
        { 404, "Not Found" },
        { 405, "Method Not Allowed" },
        { 406, "Not Acceptable" },
        { 407, "Proxy Authentication Required" },
        { 408, "Request Timeout" },
        { 409, "Conflict" },
        { 410, "Gone" },
        { 411, "Length Required" },
        { 412, "Precondition Failed" },
        { 413, "Request Entity Too Large" },
        { 414, "Request URI Too Long" },
        { 415, "Unsupported Media Type" },
        { 416, "Requested Range Not Satisfiable" },
        { 417, "Expectation Failed" },
        { 422, "Unprocessable Entity" },
        { 423, "Locked" },
        { 424, "Failed Dependency" },
        { 426, "Upgrade Required" },
        { 428, "Precondition Required" },
        { 429, "Too Many Requests" },
        { 431, "Request Header Fields Too Large" },
        { 500, "Internal Server Error" },
        { 501, "Not Implemented" },
        { 502, "Bad Gateway" },
        { 503, "Service Unavailable" },
        { 504, "Gateway Timeout" },
        { 505, "HTTP Version Not Supported" },
        { 506, "Variant Also Negotiates" },
        { 507, "Insufficient Storage" },
        { 508, "Loop Detected" },
        { 510, "Not Extended" },
        { 511, "Network Authentication Required" }
    };
    
    REQUIRE( settings.get_status_messages( ) == expectation );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[settings]" )
{
    auto settings = new Settings;
    
    REQUIRE_NOTHROW( delete settings );
}

TEST_CASE( "validate setters modify default values", "[settings]" )
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_worker_limit( 4 );
    settings.set_root( "/resources" );
    settings.set_connection_limit( 1 );
    settings.set_bind_address( "::1" );
    settings.set_case_insensitive_uris( false );
    settings.set_connection_timeout( milliseconds( 30 ) );
    settings.set_properties( { { "name", "value" } } );
    settings.set_default_headers( { { "Connection", "close" } } );
    
    REQUIRE( settings.get_port( ) == 1984 );
    REQUIRE( settings.get_root( ) == "/resources" );
    REQUIRE( settings.get_worker_limit( ) == 4 );
    REQUIRE( settings.get_bind_address( ) == "::1" );
    REQUIRE( settings.get_connection_limit( ) == 1 );
    REQUIRE( settings.get_case_insensitive_uris( ) == false );
    REQUIRE( settings.get_connection_timeout( ) == milliseconds( 30 ) );
    
    map< string, string > properties_expectation = { { "name", "value" } };
    REQUIRE( settings.get_properties( ) == properties_expectation );
    
    multimap< string, string > headers_expectation = { { "Connection", "close" } };
    REQUIRE( settings.get_default_headers( ) == headers_expectation );
}

TEST_CASE( "manipulating status messages", "[settings]" )
{
    Settings settings;
    settings.set_status_message( 418, "I'm a teapot" );
    
    SECTION( "read individual status message from valid status code" )
    {
        REQUIRE( settings.get_status_message( 418 ) == "I'm a teapot" );
    }
    
    SECTION( "read individual status message from invalid status code" )
    {
        REQUIRE( settings.get_status_message( -2 ) == "No Appropriate Status Message Found" );
    }
    
    SECTION( "read individual status message from unknown status code" )
    {
        REQUIRE( settings.get_status_message( 888 ) == "No Appropriate Status Message Found" );
    }
    
    SECTION( "read all status messages" )
    {
        map< int, string > expectation =
        {
            { 100, "Continue" },
            { 101, "Switching Protocols" },
            { 102, "Processing" },
            { 200, "OK" },
            { 201, "Created" },
            { 202, "Accepted" },
            { 203, "Non-Authoritative Information" },
            { 204, "No Content" },
            { 205, "Reset Content" },
            { 206, "Partial Content" },
            { 207, "Multi-Status" },
            { 208, "Already Reported" },
            { 226, "IM Used" },
            { 300, "Multiple Choices" },
            { 301, "Moved Permanently" },
            { 302, "Found" },
            { 303, "See Other" },
            { 304, "Not Modified" },
            { 305, "Use Proxy" },
            { 306, "Reserved" },
            { 307, "Temporary Redirect" },
            { 308, "Permanent Redirect" },
            { 400, "Bad Request" },
            { 401, "Unauthorized" },
            { 402, "Payment Required" },
            { 403, "Forbidden" },
            { 404, "Not Found" },
            { 405, "Method Not Allowed" },
            { 406, "Not Acceptable" },
            { 407, "Proxy Authentication Required" },
            { 408, "Request Timeout" },
            { 409, "Conflict" },
            { 410, "Gone" },
            { 411, "Length Required" },
            { 412, "Precondition Failed" },
            { 413, "Request Entity Too Large" },
            { 414, "Request URI Too Long" },
            { 415, "Unsupported Media Type" },
            { 416, "Requested Range Not Satisfiable" },
            { 417, "Expectation Failed" },
            { 418, "I'm a teapot" },
            { 422, "Unprocessable Entity" },
            { 423, "Locked" },
            { 424, "Failed Dependency" },
            { 426, "Upgrade Required" },
            { 428, "Precondition Required" },
            { 429, "Too Many Requests" },
            { 431, "Request Header Fields Too Large" },
            { 500, "Internal Server Error" },
            { 501, "Not Implemented" },
            { 502, "Bad Gateway" },
            { 503, "Service Unavailable" },
            { 504, "Gateway Timeout" },
            { 505, "HTTP Version Not Supported" },
            { 506, "Variant Also Negotiates" },
            { 507, "Insufficient Storage" },
            { 508, "Loop Detected" },
            { 510, "Not Extended" },
            { 511, "Network Authentication Required" }
        };
        
        REQUIRE( settings.get_status_messages( ) == expectation );
    }
}

TEST_CASE( "manipulation generic properties", "[settings]" )
{
    Settings settings;
    settings.set_property( "security-seed", "de305d54-75b4-431b-adb2-eb6b9e546014" );
    
    SECTION( "read individual property from valid name" )
    {
        REQUIRE( settings.get_property( "security-seed" ) == "de305d54-75b4-431b-adb2-eb6b9e546014" );
    }
    
    SECTION( "read individual property from uppercase name" )
    {
        REQUIRE( settings.get_property( "SECURITY-SEED" ) == "" );
    }
    
    SECTION( "read individual property from mixedcase name" )
    {
        REQUIRE( settings.get_property( "SEcURiTY-SeeD" ) == "" );
    }
    
    SECTION( "read individual propety from invalid name" )
    {
        REQUIRE( settings.get_property( "" ) == "" );
    }
    
    SECTION( "read individual property from unknown name" )
    {
        REQUIRE( settings.get_property( "realm" ) == "" );
    }
    
    SECTION( "read all properties" )
    {
        map< string, string > expectation =
        {
            { "security-seed", "de305d54-75b4-431b-adb2-eb6b9e546014" }
        };
        
        REQUIRE( settings.get_properties( ) == expectation );
    }
}
