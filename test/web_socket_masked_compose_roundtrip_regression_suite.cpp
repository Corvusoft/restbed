//System Includes
#include <cstdint>
#include <memory>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/string.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>
#include <corvusoft/restbed/detail/web_socket_manager_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::uint32_t;
using std::make_shared;

//Project Namespaces
using restbed::Bytes;
using restbed::String;
using restbed::WebSocketMessage;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

TEST_CASE( "a masked frame survives a compose/parse round-trip", "[web_socket]" )
{
    const Bytes payload = String::to_bytes( "The quick brown fox." );
    const uint32_t masking_key = 0x01020304;
    
    auto outgoing = make_shared< WebSocketMessage >( WebSocketMessage::TEXT_FRAME, payload, masking_key );
    
    WebSocketManagerImpl manager;
    const auto frame = manager.compose( outgoing );
    const auto incoming = manager.parse( frame );
    
    REQUIRE( incoming not_eq nullptr );
    REQUIRE( incoming->get_mask_flag( ) == true );
    REQUIRE( incoming->get_data( ) == payload );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
