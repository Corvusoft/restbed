#include <iostream>
#include <restbed.h>

//http://en.wikipedia.org/wiki/PATCH_(HTTP)#Request_methods

//TODO:
//web site
//ssl support

using namespace restbed;
            
Response get_handler( const Request& request )
{
    Response response;
    
    response.set_data( "hello from get handler" ); //set_body( "" );

    std::cout << "hello from get handler" << std::endl;
    
    return response;
}

int main( int, char** )
try
{
    Settings settings;
    settings.set_port( 1984 );
    settings.set_root( "resources" );

    Service service( settings );

    Resource resource;
    resource.set_path( "events/{id: .*}" ); //make sure this check is also case insentive, remove space.
    resource.set_header_filter( "Content-Type", "application/.*" ); //make sure this check is also case insentive
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


// string deduplicate( const string& value, const char target )
// {
//     string result = String::empty;

//     stringstream stream( value );

//     for ( int index = 0; index not_eq value.length( ); index++ )
//     {       
//         char character = stream.get( );

//         if ( character == target )
//         {
//             char next_character = stream.peek( );

//             if ( next_character not_eq target )
//             {
//                 result.push_back( character );
//             }
//         }
//         else
//         {
//             result.push_back( character );
//         }
//     }

//     return result;
// }


// string join( const string& format, ... )
// {
//     va_list arguments;

//     va_start( arguments, format );

//     string::size_type size = format.size( ) * 2;

//     char* result = new char[ size ];

//     int written = vsprintf( result, format.data( ), arguments );

//     while ( written < 0 )
//     {
//        delete[ ] result;

//        size *= 2;

//        result = new char[ size ];

//        written = vsprintf( result, format.data( ), arguments );
//     }

//     va_end( arguments );

//     return result;
// }




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