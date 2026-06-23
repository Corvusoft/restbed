//System Includes
#include <cstdint>
#include <memory>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>
#include <corvusoft/restbed/detail/web_socket_manager_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::byte;
using std::uint64_t;

//Project Namespaces
using restbed::Bytes;
using restbed::WebSocketMessage;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

TEST_CASE( "web socket parse decodes the full 64-bit extended length", "[web_socket]" )
{
    // FIN + binary opcode, length marker 127 (8-byte extended length follows),
    // then an unmasked 64-bit big-endian length 0x0102030405060708.
    const Bytes frame
    {
        byte{ 0x82 }, byte{ 127 },
        byte{ 0x01 }, byte{ 0x02 }, byte{ 0x03 }, byte{ 0x04 },
        byte{ 0x05 }, byte{ 0x06 }, byte{ 0x07 }, byte{ 0x08 }
    };
    
    WebSocketManagerImpl manager;
    const auto message = manager.parse( frame );
    
    REQUIRE( message not_eq nullptr );
    
    // The buggy parser reads only 4 of the 8 length bytes and overwrites the
    // accumulator with the last read, yielding 0x04 instead of the real value.
    REQUIRE( message->get_extended_length( ) == static_cast< uint64_t >( 0x0102030405060708ULL ) );
}

TEST_CASE( "web socket parse rejects a frame truncated before its mask", "[web_socket]" )
{
    // FIN + text opcode, mask bit set with a 0-length payload, but the 4 mask
    // bytes are missing. The length/mask bounds checks use unsigned arithmetic,
    // so the short-frame guard underflows and the parser reads past the end of
    // the packet. A truncated frame must be rejected with nullptr.
    const Bytes frame { byte{ 0x81 }, byte{ 0x80 }, byte{ 0x00 } };
    
    WebSocketManagerImpl manager;
    
    REQUIRE( manager.parse( frame ) == nullptr );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
