#include <iostream>
#include <restbed.h>

//http://en.wikipedia.org/wiki/PATCH_(HTTP)#Request_methods

//TODO:
//unit tests
//web site
//ssl support

using namespace restbed;
            
Response get_handler( Request& request )
{
    Response response;
    
    response.set_data( "hello from get handler" ); //set_content( "" );

    std::cout << "hello from get handler" << std::endl;
    
    return response;
}

int main( int, char** )
try
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "resources" );
    //settings.set_log( "/tmp/restbed.XXXXX.log" );
    //settings.set_log_levels( DEBUG | FATAL | INFO );
    
    Service service( settings );
        
    Resource resource;
    resource.set_path( "events/{id: .*}" ); //make sure this check is also case insentive, remove space.
    resource.set_content_type( "application/.*" ); //make sure this check is also case insentive
    resource.set_method_handler( "GET", &get_handler );
    
    service.publish( resource );
    
    service.start( );

    std::cout << "out of start" << std::endl;

    return EXIT_SUCCESS;
}
catch ( const std::exception& ex )
{
    std::cout << "exception: " << ex.what( ) << std::endl;

    return EXIT_FAILURE;
}

    //RestMQ
    //http://.../queues
    //          /queues/audit
    //          /queues/audit/register

    //Queue queue;
    //queue.set_name("audit");
    //queue.set_content_type("application/.*");
    //queue.set_handler();

    //service.publish( queue );

    //consumer.register(event);
