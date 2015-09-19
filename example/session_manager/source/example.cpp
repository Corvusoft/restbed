/*
 * Example illustrating session management.
 *
 * Server Usage:
 *    ./distribution/example/session_manager
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/resource?location=UK'
 *    curl -w'\n' -v -X GET 'http://localhost:1984/resource' -H"SessionID: <Previously returned SessionID header value>"
 */

#include <map>
#include <chrono>
#include <string>
#include <memory>
#include <random>
#include <cstdlib>
#include <restbed>

using namespace std;
using namespace restbed;

class InMemorySessionManager : public SessionManager
{
public:
	InMemorySessionManager( void ) : sessions( )
    {
        return;
    }
    
    ~InMemorySessionManager( void )
    {
        return;
    }
    
    void start( const shared_ptr< const Settings >& )
    {
        return;
    }
    
    void create( const function< void ( const shared_ptr< Session > ) >& callback )
    {
        static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static uniform_int_distribution< > selector( 0, charset.size( ) - 1 );
        static mt19937 generator( chrono::high_resolution_clock::now( ).time_since_epoch( ).count( ) );
        
        string key = "";
        for ( int index = 0; index < 32; index++ )
        {
            key += charset.at( selector( generator ) );
        }

        auto session = make_shared< Session >( key );
        
        callback( session );
    }
    
    void load( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        const auto request = session->get_request( );
        auto previous_session = sessions.find( request->get_header( "SessionID" ) );

        if ( previous_session not_eq sessions.end( ) )
        {
            const auto key = previous_session->second->get_id( );
            session->set_id( key );
            session->set_header( "SessionID", key );

            for ( const auto key : previous_session->second->keys( ) )
            {
                session->set( key, previous_session->second->get( key ) );
            }
        }
        else
        {
            const auto key = session->get_id( );
            session->set_id( key );
            session->set_header( "SessionID", key );
        }
        
        callback( session );
    }

    void save( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        sessions[ session->get_id( ) ] = session;
        callback( session );
    }

    void stop( void )
    {
        return;
    }

private:
	map< string, shared_ptr< Session > > sessions;
};

void get_method_handler( const shared_ptr< Session > session )
{
    string body = "Previous Session Data\n";

    for ( const auto key : session->keys( ) )
    {
        string value = session->get( key );
        body += key + "=" + value + "\n";
    }

    const auto request = session->get_request( ); 

    for ( const auto query_parameter : request->get_query_parameters( ) )
    {
        session->set( query_parameter.first, query_parameter.second );
    }

    session->close( OK, body, { { "Connection", "close" } } );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    Service service;
    service.publish( resource );
    service.set_session_manager( make_shared< InMemorySessionManager >( ) );
    service.start( settings );
    
    return EXIT_SUCCESS;
}
