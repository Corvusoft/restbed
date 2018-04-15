//System Includes
#include <chrono>
#include <thread>
#include <string>
#include <memory>
#include <vector>
#include <ciso646>
#include <stdexcept>
#include <functional>
#include <system_error>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch.hpp>

//System Namespaces
using std::thread;
using std::string;
using std::vector;
using std::error_code;
using std::shared_ptr;
using std::make_shared;
using std::chrono::seconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::ip::tcp;
using asio::connect;
using asio::io_service;
using asio::socket_base;

void get_handler( const shared_ptr< Session > session )
{
    session->close( 200 );
}

SCENARIO( "validate connection timeout after connect", "[socket]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_connection_timeout( seconds( 2 ) );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I create a service with a socket connection timeout of '2' seconds" )
            {
                WHEN( "I establish a network connection and wait '4' seconds" )
                {
                    io_service io_service;
                    asio::ip::tcp::socket socket( io_service );
                    asio::ip::tcp::endpoint endpoint( asio::ip::address::from_string( "127.0.0.1" ), 1984 );

                    error_code error;
                    socket.connect( endpoint, error );
                    
                    REQUIRE( true == socket.is_open( ) );
                    
                    std::this_thread::sleep_for( seconds( 4 ) );
                    
                    THEN( "I should see the peer close the socket" )
                    {
                        uint8_t data;
                        asio::error_code error;
                        socket.receive( asio::buffer( &data, 1 ), socket_base::message_peek, error );
                        
                        REQUIRE( ( error == asio::error::eof or error == asio::error::connection_reset ) );
                    }
                    
                    socket.close( );
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}

SCENARIO( "validate connection timeout after partial request", "[socket]" )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/resource" );
    resource->set_method_handler( "GET", get_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    settings->set_connection_timeout( seconds( 2 ) );
    
    shared_ptr< thread > worker = nullptr;
    
    Service service;
    service.publish( resource );
    service.set_ready_handler( [ &worker ]( Service & service )
    {
        worker = make_shared< thread >( [ &service ] ( )
        {
            GIVEN( "I create a service with a socket connection timeout of '2' seconds" )
            {
                AND_THEN( "I perform a partial HTTP request" )
                {
                    io_service io_service;
                    asio::ip::tcp::socket socket( io_service );
                    asio::ip::tcp::endpoint endpoint( asio::ip::address::from_string( "127.0.0.1" ), 1984 );

                    error_code error;
                    socket.connect( endpoint, error );
                    
                    REQUIRE( true == socket.is_open( ) );
                    
                    string request = "GET /resource HTTP/1.1\r\n";
                    socket.send( asio::buffer( request, request.length( ) ), 0, error );
                    
                    WHEN( "I wait '4' seconds" )
                    {
                        std::this_thread::sleep_for( seconds( 4 ) );
                        
                        THEN( "I should see the peer close the socket" )
                        {
                            uint8_t data;
                            asio::error_code error;
                            socket.receive( asio::buffer( &data, 1 ), socket_base::message_peek, error );
                            
                            REQUIRE( ( error == asio::error::eof or error == asio::error::connection_reset ) );
                        }
                        
                        socket.close( );
                    }
                }
                
                service.stop( );
            }
        } );
    } );
    
    service.start( settings );
    worker->join( );
}
