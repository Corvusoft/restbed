#include <string>
#include <memory>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

void get_xml_method_handler( const shared_ptr< Session >& session )
{
    session->close( 200, "<hello><world></world></hello>" ); //header "Content-Type", "application/xml"
}

void get_json_method_handler( const shared_ptr< Session >& session )
{
    session->close( 200, "{ \"Hello\": \", World!\" }" ); //header "Content-Type", "application/json"
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", { { "Accept", "application/xml" }, { "Content-Type", "application/xml" } }, &get_xml_method_handler );
    resource->set_method_handler( "GET", { { "Accept", "application/json" }, { "Content-Type", "application/json" } }, &get_json_method_handler );
    
    Settings settings;
    settings.set_port( 1984 );
    
    Service service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
