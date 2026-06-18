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

TEST_CASE( "WebSocketMessage::to_bytes derives the length from the payload", "[web_socket_message]" )
{
    // Construct with a two-octet payload (length field becomes 2), then replace
    // the payload via set_data without touching the length field. The emitted
    // frame must declare the real payload length, not the stale field value.
    WebSocketMessage message( WebSocketMessage::OpCode::TEXT_FRAME, String::to_bytes( "Hi" ) );
    message.set_data( String::to_bytes( "Hello" ) );

    const Bytes expected =
    {
        byte{ 0x81 }, byte{ 0x05 },
        byte{ 'H' }, byte{ 'e' }, byte{ 'l' }, byte{ 'l' }, byte{ 'o' }
    };

    REQUIRE( message.to_bytes( ) == expected );
}

TEST_CASE( "WebSocketMessage::to_bytes encodes a 16-bit extended length", "[web_socket_message]" )
{
    const Bytes payload( 200, byte{ 0x61 } );
    const WebSocketMessage message( WebSocketMessage::OpCode::TEXT_FRAME, payload );

    const auto frame = message.to_bytes( );

    REQUIRE( frame.size( ) == 4 + payload.size( ) );
    REQUIRE( frame[ 0 ] == byte{ 0x81 } );  // FIN + TEXT_FRAME
    REQUIRE( frame[ 1 ] == byte{ 126 } );   // 16-bit extended-length marker, unmasked
    REQUIRE( frame[ 2 ] == byte{ 0x00 } );  // 200 == 0x00C8, big-endian
    REQUIRE( frame[ 3 ] == byte{ 0xC8 } );
    REQUIRE( Bytes( frame.begin( ) + 4, frame.end( ) ) == payload );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
