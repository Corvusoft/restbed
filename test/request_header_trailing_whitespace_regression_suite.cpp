//System Includes
#include <map>
#include <string>
#include <sstream>

//Project Includes
#include <corvusoft/restbed/detail/service_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;
using std::multimap;
using std::istringstream;

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

TEST_CASE( "request header values are stripped of trailing whitespace", "[service]" )
{
    // RFC 7230 3.2.4: leading and trailing optional whitespace ( OWS ) is not
    // part of a header field value. The parser's regex carried a trailing \s* to
    // strip it, but the greedy value group swallowed the spaces first ( and '.'
    // never matches the line's terminating CR ), so only the CR was ever
    // consumed and trailing spaces survived.
    istringstream stream( "Host: example.com  \r\nConnection: keep-alive\t\r\nMulti:  inner  value  \r\nEmpty:\r\n\r\n" );
    
    const multimap< string, string > headers = ServiceImpl::parse_request_headers( stream );
    
    REQUIRE( headers.find( "Host" )->second == "example.com" );
    REQUIRE( headers.find( "Connection" )->second == "keep-alive" );
    // Internal whitespace must be preserved; only the trailing run is removed.
    REQUIRE( headers.find( "Multi" )->second == "inner  value" );
    REQUIRE( headers.find( "Empty" )->second == "" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
