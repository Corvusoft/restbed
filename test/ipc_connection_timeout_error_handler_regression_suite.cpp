//System Includes
#include <mutex>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <cstdio>
#include <stdexcept>
#include <system_error>
#include <condition_variable>

//Project Includes
#include <restbed>

//External Includes
#include <asio.hpp>
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::mutex;
using std::string;
using std::thread;
using std::exception;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::unique_lock;
using std::condition_variable;
using std::chrono::seconds;
using std::chrono::milliseconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using asio::io_context;
using asio::local::stream_protocol;

namespace
{
    mutex g_mutex;
    condition_variable g_condition;
    bool g_fired = false;
    int g_status = 0;

    void error_handler( const int status, const exception&, const shared_ptr< Session > )
    {
        // The timeout path intentionally passes a null session; never touch it.
        unique_lock< mutex > lock( g_mutex );

        if ( not g_fired )
        {
            g_fired = true;
            g_status = status;
            g_condition.notify_all( );
        }
    }
}

TEST_CASE( "ipc connection timeout invokes service error handler", "[ipc]" )
{
    const string socket_path = "/tmp/restbed_ipc_timeout_regression.sock";
    ::remove( socket_path.data( ) );

    auto settings = make_shared< Settings >( );
    settings->set_port( 0 );
    settings->set_ipc_path( socket_path );
    settings->set_connection_timeout( milliseconds( 250 ) );

    shared_ptr< thread > worker = nullptr;

    Service service;
    service.set_error_handler( error_handler );
    service.set_ready_handler( [ &worker, socket_path ]( Service & service )
    {
        worker = make_shared< thread >( [ &service, socket_path ]( )
        {
            io_context io;
            stream_protocol::socket socket( io );

            error_code error;
            socket.connect( stream_protocol::endpoint( socket_path ), error );

            if ( not error )
            {
                // Deliberately send nothing so the server's request read times out.
                unique_lock< mutex > lock( g_mutex );
                g_condition.wait_for( lock, seconds( 5 ), [ ]( ) { return g_fired; } );
                lock.unlock( );
            }

            error_code ignored;
            socket.close( ignored );
            service.stop( );
        } );
    } );

    service.start( settings );
    worker->join( );
    ::remove( socket_path.data( ) );

    REQUIRE( g_fired );
    REQUIRE( g_status == 408 );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
