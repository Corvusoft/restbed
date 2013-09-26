#include <iostream>
#include <restbed>

//TODO:
//web site
//ssl support

using namespace restbed;
            
Response get_handler( const Request& request )
{
    Response response;
    response.set_body( "hello from get handler" );
    response.set_header( "Forename", "Ben" );
    response.set_status_code( StatusCode::CREATED );

    std::cout << "hello from get handler" << std::endl;
    
    return response;
}
//exception trace!!!

int main( int, char** )
try
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "resources" );

    Service service( settings );

    Resource resource;
    resource.set_path( "events/{id: .*}" ); //make sure this check is also ignores case , remove space.
    resource.set_header_filter( "Content-Type", "application/.*" ); //make sure this check is also ignores case.
    resource.set_method_handler( "GET", &get_handler );

    service.publish( resource );
    
    service.start( );

    std::cout << "out of start" << std::endl;

    return EXIT_SUCCESS;
}
catch ( const std::exception& ex )
{
    std::cout << "restbed failed: " << ex.what( ) << std::endl;

    return EXIT_FAILURE;
}

//example
// Resource json_resource;
// json_resource.set_path('/api');
// json_resource.set_header_filter('content-type', 'application/json');

// Resource xml_resource;
// xml_resource.set_path('/api');
// xml_resource.set_header_filter('content-type', 'application/xml');

    //RestMQ
    //http://.../queues
    //          /queues/audit/stats
    //          /queues/audit/message
    //          /queues/audit/register
    //          /queues/audit/unregister

    //Queue queue;
    //queue.set_type(); //fanout etc...
    //queue.set_name("audit");
    //queue.set_content_type("application/.*"); //optional
    //queue.set_stats_handler(); //optional
    //queue.set_register_handler(); //optional
    //queue.set_unregister_handler(); //optional
    //queue.set_message_handler(); //optional

    //Exchange exchange;
    //exchange.set_authentication_handler( );
    //exchange.set_root( string root = "queues" ); //optional
    //exchange.set_storage_handler( StorageCallbacks callbacks ) //optional, default = MemoryCallbacks
    //exchange.open/publish????( queue );
    //set_log_handler

    //Publisher publisher('http://../queues/audit');
    //publisher.publish( Message );

    //Consumer consumer = Consumer::register('http://user:pass@localhost:80/queues/audit');
    //consumer.set_message_handler() //optional, default ignore.