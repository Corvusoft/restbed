//System Includes
#include <cstdint>
#include <cstddef>
#include <memory>

//Project Includes
#include <corvusoft/restbed/settings.hpp>
#include <corvusoft/restbed/detail/web_socket_impl.hpp>
#include <corvusoft/restbed/detail/web_socket_manager_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::size_t;
using std::make_shared;

//Project Namespaces
using restbed::Settings;
using restbed::detail::WebSocketImpl;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

TEST_CASE( "a max frame size of zero imposes no configured limit", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length_within_limit( 125, 0, 0 ) == true );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0x7FFFFFFFFFFFFFFFULL, 0 ) == true );
}

TEST_CASE( "the configured max frame size bounds the payload length", "[web_socket]" )
{
    // Boundary: a payload exactly at the limit is accepted, one octet over is not.
    REQUIRE( WebSocketImpl::payload_length_within_limit( 126, 1000, 1000 ) == true );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 126, 1001, 1000 ) == false );
    
    // The limit also applies to small ( non-extended ) frames.
    REQUIRE( WebSocketImpl::payload_length_within_limit( 10, 0, 5 ) == false );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 5, 0, 5 ) == true );
}

TEST_CASE( "the RFC 6455 most-significant-bit rule is enforced regardless of the configured max", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0x8000000000000000ULL, 0 ) == false );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0x8000000000000000ULL, 1000 ) == false );
}

TEST_CASE( "the max frame size defaults to unlimited and round-trips through Settings", "[settings]" )
{
    Settings settings;
    REQUIRE( settings.get_web_socket_max_frame_size( ) == static_cast< size_t >( 0 ) );
    
    settings.set_web_socket_max_frame_size( 4096 );
    REQUIRE( settings.get_web_socket_max_frame_size( ) == static_cast< size_t >( 4096 ) );
}

TEST_CASE( "the WebSocket manager carries the max frame size", "[web_socket]" )
{
    auto manager = make_shared< WebSocketManagerImpl >( );
    REQUIRE( manager->get_max_frame_size( ) == static_cast< size_t >( 0 ) );
    
    manager->set_max_frame_size( 2048 );
    REQUIRE( manager->get_max_frame_size( ) == static_cast< size_t >( 2048 ) );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
