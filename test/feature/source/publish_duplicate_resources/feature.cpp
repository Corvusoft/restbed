//System Includes
#include <string>
#include <memory>
#include <stdexcept>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::invalid_argument;

//Project Namespaces
using namespace restbed;

//External Namespaces

SCENARIO( "publishing duplicate resources", "[service]" )
{
    GIVEN( "I publish a resource at '/resources/1'" )
    {
        auto resource = make_shared< Resource >( );
        resource->set_path( "/resources/1" );
        
        auto settings = make_shared< Settings >( );
        settings->set_port( 1984 );
        
        Service service;
        service.publish( resource );
        
        WHEN( "I attempt to publish another resource at '/resources/1'" )
        {
            THEN( "I should see an invalid argument error of 'Resource would pollute namespace. Please ensure all published resources have unique paths.'" )
            {
                REQUIRE_THROWS_AS( service.publish( resource ), invalid_argument );
            }
        }
        
        service.stop( );
    }
}
