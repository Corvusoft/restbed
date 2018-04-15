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

class ContentLengthRule : public Rule
{
    public:
        ContentLengthRule( void ) : Rule( )
        {
            return;
        }
        
        virtual ~ContentLengthRule( void )
        {
            return;
        }
        
        bool condition( const shared_ptr< Session > session ) final override
        {
            return session->get_request( )->get_method( String::uppercase ) == "POST";
        }
        
        void action( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback ) final override
        {
            const auto request = session->get_request( );
            
            if ( not request->has_header( "Content-Length" ) )
            {
                session->close( LENGTH_REQUIRED, "Length Required.", { { "Content-Length", "16" }, { "Content-Type", "text/plain" } } );
            }
            else
            {
                size_t length = request->get_header( "Content-Length", 0 );
                
                session->fetch( length, [ length, callback ]( const shared_ptr< Session > session, const Bytes & body )
                {
                    if ( length not_eq body.size( ) )
                    {
                        session->close( LENGTH_REQUIRED, "Length Required.", { { "Content-Length", "16" }, { "Content-Type", "text/plain" } } );
                    }
                    else
                    {
                        callback( session );
                    }
                } );
            }
        }
};
