#include "restbed"

using namespace restbed;

class BasicAuthService : public Service
{
    public:
        BasicAuthService( const Settings& settings ) : Service( settings )
        {
            //n/a
        }

        virtual ~BasicAuthService( void )
        {
            //n/a
        }

        void authentication_handler( const Request& request, /*out*/ Response& response )
        {
            auto authorisation = request.get_header( "Authorization" );

            if ( authorisation == "Basic Q29ydnVzb2Z0OkdsYXNnb3c=" )
            {
                response.set_status_code( 200 );
            }
            else
            {
                response.set_status_code( 401 );
                response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
            }
        }
};

Response get_method_handler( const Request& )
{
    Response response;
    response.set_body( "Password Protected Hello, World!" );
    response.set_status_code( StatusCode::OK );

    return response;
}

int main( int, char** )
{
    Resource resource;
    resource.set_path( "/resource" );
    resource.set_method_handler( "GET", &get_method_handler );

    Settings settings;
    settings.set_port( 1984 );

    BasicAuthService service( settings );
    service.publish( resource );
    service.start( );

    return EXIT_SUCCESS;
}
