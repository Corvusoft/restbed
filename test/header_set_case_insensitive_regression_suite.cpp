//System Includes
#include <string>

//Project Includes
#include <corvusoft/restbed/request.hpp>
#include <corvusoft/restbed/response.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Request;
using restbed::Response;

//External Namespaces

TEST_CASE( "Response::set_header replaces an existing header regardless of name case", "[response]" )
{
    Response response;
    response.set_header( "Content-Type", "text/html" );

    // HTTP header field names are case-insensitive ( RFC 7230 3.2 ), so this
    // must replace the value above rather than add a second Content-Type.
    response.set_header( "content-type", "application/json" );

    REQUIRE( response.get_headers( "content-type" ).size( ) == 1 );
    REQUIRE( response.get_header( "content-type" ) == "application/json" );
}

TEST_CASE( "Request::set_header replaces an existing header regardless of name case", "[request]" )
{
    Request request;
    request.set_header( "Accept", "text/html" );
    request.set_header( "accept", "application/json" );

    REQUIRE( request.get_headers( "accept" ).size( ) == 1 );
    REQUIRE( request.get_header( "accept" ) == "application/json" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
