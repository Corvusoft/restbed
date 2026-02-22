//System Includes

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/response.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces

//Project Namespaces
using restbed::Bytes;
using restbed::Response;

//External Namespaces

TEST_CASE( "validate default instance values", "[response]" )
{
    const Response response;
    REQUIRE( response.get_body( ).empty( ) );
}

TEST_CASE( "validate setters modify default values", "[response]" )
{
    Bytes expectation = { std::byte('a'), std::byte('b') };
    
    Response response;
    response.set_body( expectation );
    
    const auto body = response.get_body( );
    REQUIRE( body == expectation );
}

int main(int argc, char* argv[])
{
    return Catch::Session().run(argc, argv);
}
