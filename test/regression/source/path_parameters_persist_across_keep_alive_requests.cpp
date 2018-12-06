//System Includes
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::function;
using std::make_shared;
using std::shared_ptr;
using std::string;
using std::thread;

//Project Namespaces
using namespace restbed;

//External Namespaces

void get_handler( const shared_ptr< Session > session )
{
    auto request = session->get_request( );
    auto path_parameter = request->get_path_parameter( "userId" );

    string previous_value = session->get( "userId", string( ) );

    if (previous_value != "") {
        REQUIRE( path_parameter != previous_value );
    }

    session->set( "userId", path_parameter );

    session->set_header( "Connection", "keep-alive" );
    session->yield( 200 );
}

TEST_CASE( "path parameters persist across keep-alive requests", "[request]" )
{
    auto resource = make_shared<Resource>( );
    resource->set_path( "/users/{userId: ^\\d+$}/profile" );
    resource->set_method_handler( "GET", get_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );

    shared_ptr< thread > worker = nullptr;

    Service service;
    service.publish( resource );

    service.set_ready_handler( [ &worker ]( Service &service )
    {
        worker = make_shared< thread >( [ &service ]( )
        {
            auto request = make_shared< Request >( );
            request->set_port( 1984 );
            request->set_host( "localhost" );
            request->set_header( "Connection", "keep-alive" );

            request->set_path( "/users/1/profile" );
            auto response = Http::sync( request );

            request->set_path( "/users/2/profile" );
            response = Http::sync( request );

            request->set_path( "/users/3/profile" );
            response = Http::sync( request );

            request->set_path( "/users/100/profile" );
            response = Http::sync( request );

            service.stop();
        } );
    } );

    service.start( settings );
    worker->join( );
}