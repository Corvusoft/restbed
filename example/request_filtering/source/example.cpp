#include "restbed"

using namespace restbed;

Response get_xml_method_handler( const Request& )
{
    Response response;
    response.set_body( "<hello><world></world></hello>" );
    response.set_header( "Content-Type", "application/xml" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}

Response get_json_method_handler( const Request& )
{
    Response response;
    response.set_body( "{ \"Hello\": \", World!\" }" );
    response.set_header( "Content-Type", "application/json" );
    response.set_status_code( StatusCode::OK );
    
    return response;
}
int main( int, char** )
{
    Resource xml;
    xml.set_path( "/resource" );
    xml.set_header_filter( "Accept", "application/xml" );
    xml.set_method_handler( "GET", &get_xml_method_handler );
    
    Resource json;
    json.set_path( "/resource" );
    json.set_header_filter( "Accept", "application/json" );
    json.set_method_handler( "GET", &get_json_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( xml );
    service.publish( json );
    service.start( );
    
    return EXIT_SUCCESS;
}
