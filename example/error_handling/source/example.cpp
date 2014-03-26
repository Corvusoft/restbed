#include "restbed"

using namespace restbed;

class ErrorHandlingService : public Service
{
    public:
        ErrorHandlingService( const Settings& settings ) : Service( settings )
        {
            //n/a
        }
        
        virtual ~ErrorHandlingService( void )
        {
            //n/a
        }
        
        void error_handler( const Request&, /*out*/ Response& response )
        {
            response.set_status_code( 500 );
            response.set_body( "yikes! we've got a problem." );
        }
};

int main( int, char** )
{
    Resource resource;
    
    Settings settings;
    settings.set_port( 1984 );
    
    ErrorHandlingService service( settings );
    service.publish( resource );
    service.start( );
    
    return EXIT_SUCCESS;
}
