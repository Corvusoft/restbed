#include <string>
#include <memory>
#include <ciso646>
#include <functional>
#include <restbed>

using namespace std;
using namespace restbed;

class HostRule : public Rule
{
    public:
        HostRule( void ) : Rule( )
        {
            return;
        }
        
        virtual ~HostRule( void )
        {
            return;
        }
        
        bool condition( const shared_ptr< Session > ) final override
        {
            return true;
        }
        
        void action( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback ) final override
        {
            const auto request = session->get_request( );
            
            if ( not request->has_header( "Host" ) )
            {
                session->close( BAD_REQUEST, "Bad Request! Host header required.", { { "Content-Length", "34" }, { "Content-Type", "text/plain" } } );
            }
            else
            {
                callback( session );
            }
        }
};
