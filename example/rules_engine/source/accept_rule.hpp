#include <string>
#include <memory>
#include <ciso646>
#include <functional>
#include <restbed>

using namespace std;
using namespace restbed;

class AcceptRule : public Rule
{
    public:
        AcceptRule( void ) : Rule( )
        {
            return;
        }
        
        virtual ~AcceptRule( void )
        {
            return;
        }
        
        bool condition( const shared_ptr< Session > session ) final override
        {
            return session->get_request( )->has_header( "Accept" );
        }
        
        void action( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback ) final override
        {
            const auto request = session->get_request( );
            const auto type = request->get_header( "Accept", String::lowercase );
            
            if ( type not_eq "text/plain" and type not_eq "*/*" )
            {
                session->close( NOT_ACCEPTABLE,
                                "Not Acceptable, must be 'text/plain' or '*/*'.",
                { { "Content-Length", "46" }, { "Content-Type", "text/plain" } } );
            }
            else
            {
                callback( session );
            }
        }
};
