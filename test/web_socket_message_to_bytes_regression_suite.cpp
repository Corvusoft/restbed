//System Includes
#include <cstddef>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/string.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::byte;

//Project Namespaces
using restbed::Bytes;
using restbed::String;
using restbed::WebSocketMessage;

//External Namespaces

TEST_CASE( "WebSocketMessage::to_bytes serialises an unmasked frame", "[web_socket_message]" )
{
    const WebSocketMessage message( WebSocketMessage::OpCode::TEXT_FRAME, String::to_bytes( "Hi" ) );

    // FIN + TEXT_FRAME (0x81), unmasked length 2, then the payload octets.
    const Bytes expected = { byte{ 0x81 }, byte{ 0x02 }, byte{ 'H' }, byte{ 'i' } };

    REQUIRE( message.to_bytes( ) == expected );
}

TEST_CASE( "WebSocketMessage::to_bytes serialises a masked frame", "[web_socket_message]" )
{
    const WebSocketMessage message( WebSocketMessage::OpCode::PING_FRAME, String::to_bytes( "C" ), 0x01020304 );

    // FIN + PING_FRAME (0x89); MASK bit set on the length byte (0x81); the four
    // masking-key octets in transmitted order; then the payload masked with
    // key[0] ( 'C' ^ 0x01 == 0x42 ).
    const Bytes expected =
    {
        byte{ 0x89 }, byte{ 0x81 },
        byte{ 0x01 }, byte{ 0x02 }, byte{ 0x03 }, byte{ 0x04 },
        byte{ 0x42 }
    };

    REQUIRE( message.to_bytes( ) == expected );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
