//System Includes
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::uint64_t;

//Project Namespaces
using restbed::Bytes;
using restbed::WebSocketMessage;

//External Namespaces

TEST_CASE( "65535-byte payload uses the 16-bit length marker", "[web_socket]" )
{
    const WebSocketMessage message( WebSocketMessage::BINARY_FRAME, Bytes( 65535 ) );
    
    REQUIRE( unsigned( message.get_length( ) ) == 126u );
    REQUIRE( message.get_extended_length( ) == static_cast< uint64_t >( 65535 ) );
}

TEST_CASE( "65536-byte payload uses the 64-bit length marker", "[web_socket]" )
{
    const WebSocketMessage message( WebSocketMessage::BINARY_FRAME, Bytes( 65536 ) );
    
    REQUIRE( unsigned( message.get_length( ) ) == 127u );
    REQUIRE( message.get_extended_length( ) == static_cast< uint64_t >( 65536 ) );
}

TEST_CASE( "126-byte payload is the lower bound of the 16-bit marker", "[web_socket]" )
{
    const WebSocketMessage extended( WebSocketMessage::BINARY_FRAME, Bytes( 126 ) );
    REQUIRE( unsigned( extended.get_length( ) ) == 126u );
    
    const WebSocketMessage inline_length( WebSocketMessage::BINARY_FRAME, Bytes( 125 ) );
    REQUIRE( unsigned( inline_length.get_length( ) ) == 125u );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
