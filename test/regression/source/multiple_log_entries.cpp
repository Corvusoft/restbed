//System Includes
#include <regex>
#include <cstdio>
#include <thread>
#include <memory>
#include <chrono>
#include <vector>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::regex;
using std::thread;
using std::string;
using std::vector;
using std::vsnprintf;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces

class CustomLogger : public Logger
{
    public:
        CustomLogger( void ) : actual( )
        {
            return;
        }
        
        void stop( void )
        {
            return;
        }
        
        void start( const shared_ptr< const Settings >& )
        {
            return;
        }
        
        void log( const Level, const char* format, ... )
        {
            va_list arguments;
            va_start( arguments, format );
            
            va_list temporary;
            va_copy( temporary, arguments );
            const auto length = vsnprintf( nullptr, 0, format, temporary ) + 1;
            va_end( temporary );
            
            string buffer;
            buffer.resize( length );
            
            if ( vsnprintf( &buffer[ 0 ], length, format, arguments ) < 0 )
            {
                throw runtime_error( "" );
            }
            
            buffer.pop_back( );
            actual.push_back( buffer );
            
            va_end( arguments );
        }
        
        void log_if( bool expression, const Level level, const char* format, ... )
        {
            if ( expression )
            {
                va_list arguments;
                va_start( arguments, format );
                log( level, format, arguments );
                va_end( arguments );
            }
        }
        
        vector< string > actual;
};

void get_handler( const shared_ptr< Session > session )
{
    session->close( OK, "OK", { { "Connection", "close" } } );
}

TEST_CASE( "multiple log entries", "[service]" )
{
    auto resource_one = make_shared< Resource >( );
    resource_one->set_path( "resource_one" );
    resource_one->set_method_handler( "GET", get_handler );
    
    auto resource_two = make_shared< Resource >( );
    resource_two->set_path( "resource_two" );
    resource_two->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    auto logger = make_shared< CustomLogger >( );
    
    Service service;
    service.publish( resource_one );
    service.publish( resource_two );
    service.set_logger( logger );
    service.set_ready_handler( [ &worker, &logger ]( Service & service )
    {
        worker = make_shared< thread >( [ &service, &logger ] ( )
        {
            auto request = make_shared< Request >( );
            request->set_method( "GET" );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_path( "/resource_two" );
            
            auto response = Http::sync( request );
            
            REQUIRE( 200 == response->get_status_code( ) );
            
            REQUIRE( regex_match( logger->actual[ 0 ], regex( "^Service accepting HTTP connections at '.*'\\.$" ) ) );
            REQUIRE( regex_match( logger->actual[ 1 ], regex( "^Resource published on route '/resource_one'\\.$" ) ) );
            REQUIRE( regex_match( logger->actual[ 2 ], regex( "^Resource published on route '/resource_two'\\.$" ) ) );
            REQUIRE( regex_match( logger->actual[ 3 ], regex( "^Incoming 'GET' request from '.*' for route '/resource_two'\\.$" ) ) );
            
            REQUIRE( 4 == logger->actual.size( ) );
            
            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
