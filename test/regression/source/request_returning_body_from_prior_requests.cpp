//System Includes
#include <thread>
#include <memory>
#include <stdexcept>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces
using namespace restbed;

//External Namespaces

void post_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    size_t content_length = request->get_header( "Content-Length", 0 );

    session->fetch( content_length, [ ]( const shared_ptr< Session > session, const Bytes& )
    {
        const auto length = std::to_string( session->get_request( )->get_body( ).size( ) );
        session->yield( OK, session->get_request()->get_body( ), { { "Content-Length", length }, { "Connection", "keep-alive" } } );
    } );
}

TEST_CASE( "request returning body from prior requests", "[request]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "POST", post_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_body( "test" );
            request->set_method( "POST" );
            request->set_host( "localhost" );
            request->set_path( "/resource" );
            request->add_header( "Content-Length", "4" );
            request->add_header( "Connection", "keep-alive" );

            auto response = Http::sync( request );
            REQUIRE( 200 == response->get_status_code( ) );

            Bytes expectation = { 't', 'e', 's', 't' };
            Http::fetch( expectation.size( ), response );
            REQUIRE( expectation == response->get_body( ) );
            
            response = Http::sync( request );
            REQUIRE( 200 == response->get_status_code( ) );

            try {
                Http::fetch( expectation.size( ) * 2, response );
            } catch ( const runtime_error& ) {
                Http::fetch( expectation.size( ), response );
                REQUIRE( expectation == response->get_body( ) );
            }

            service.stop( );
        } );
    } );
    service.start( settings );
    worker->join( );
}
