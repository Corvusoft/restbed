//System Includes
#include <chrono>

//Project Includes
#include <corvusoft/restbed/service.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::chrono::seconds;
using std::chrono::steady_clock;

//Project Namespaces
using restbed::Service;

//External Namespaces

TEST_CASE( "confirm default constructor throws no exceptions", "[service]" )
{
    REQUIRE_NOTHROW( new Service );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[service]" )
{
    auto service = new Service;
    
    REQUIRE_NOTHROW( delete service );
}

TEST_CASE( "confirm calling stop before start throws no exceptions", "[service]" )
{
    Service service;
    
    REQUIRE_NOTHROW( service.stop( ) );
}

TEST_CASE( "confirm default service state", "[service]" )
{
    Service service;
    
    REQUIRE( service.is_down( ) );
    REQUIRE_FALSE( service.is_up( ) );
    REQUIRE( service.get_uptime( ) == seconds( 0 ) );
}
