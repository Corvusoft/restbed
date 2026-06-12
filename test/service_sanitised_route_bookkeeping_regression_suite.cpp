//System Includes
#include <memory>
#include <stdexcept>

//Project Includes
#include <corvusoft/restbed/service.hpp>
#include <corvusoft/restbed/resource.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::make_shared;
using std::invalid_argument;

//Project Namespaces
using restbed::Service;
using restbed::Resource;

//External Namespaces

TEST_CASE( "two resources whose parameterised routes collide are rejected", "[service]" )
{
    auto first = make_shared< Resource >( );
    first->set_path( "/resource/{id: [0-9]+}" );

    auto second = make_shared< Resource >( );
    second->set_path( "/resource/{key: [0-9]+}" );

    Service service;
    service.publish( first );

    REQUIRE_THROWS_AS( service.publish( second ), invalid_argument );
}

TEST_CASE( "suppress removes a parameterised route so it can be re-published", "[service]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource/{id: [0-9]+}" );

    Service service;
    service.publish( resource );
    service.suppress( resource );

    REQUIRE_NOTHROW( service.publish( resource ) );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
