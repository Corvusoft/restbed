//System Includes
#include <string>
#include <memory>
#include <ciso646>
#include <functional>

//Project Includes
#include <restbed>

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::shared_ptr;

//Project Namespaces
using namespace restbed;

//External Namespaces

class ContentTypeRule : public Rule
{
    public:
        ContentTypeRule( void ) : Rule( )
        {
            return;
        }
        
        virtual ~ContentTypeRule( void )
        {
            return;
        }
        
        bool condition( const shared_ptr< Session > session ) final override
        {
            return session->get_request( )->has_header( "Content-Type" );
        }
        
        void action( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback ) final override
        {
            const auto request = session->get_request( );
            
            if ( request->get_header( "Content-Type", String::lowercase ) not_eq "application/csv" )
            {
                session->close( UNSUPPORTED_MEDIA_TYPE, "Unsupported Media Type, must be 'application/csv'.", { { "Content-Length", "50" }, { "Content-Type", "text/plain" } } );
            }
            else
            {
                callback( session );
            }
        }
};
