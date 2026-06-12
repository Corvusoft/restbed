//System Includes
#include <clocale>

//Project Includes
#include <corvusoft/restbed/detail/service_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//Project Namespaces
using restbed::detail::ServiceImpl;

//External Namespaces

TEST_CASE( "parse_http_version is independent of the global locale", "[service]" )
{
    std::setlocale( LC_ALL, "de_DE.utf8" );

    REQUIRE( ServiceImpl::parse_http_version( "1.1" ) == 1.1 );
    REQUIRE( ServiceImpl::parse_http_version( "1.0" ) == 1.0 );
    REQUIRE( ServiceImpl::parse_http_version( "2.0" ) == 2.0 );

    std::setlocale( LC_ALL, "C" );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
