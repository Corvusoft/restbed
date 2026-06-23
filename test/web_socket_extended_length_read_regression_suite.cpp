//System Includes
#include <cstddef>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/web_socket_message.hpp>
#include <corvusoft/restbed/detail/web_socket_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::size_t;
using std::uint8_t;

//Project Namespaces
using restbed::detail::WebSocketImpl;

//External Namespaces

TEST_CASE( "frame header remainder for 64-bit extended length", "[web_socket]" )
{
    // 8 bytes of extended length; the buggy implementation read only 4.
    REQUIRE( WebSocketImpl::frame_header_remainder( 127, false ) == static_cast< size_t >( 8 ) );
    
    // ...plus the 4-byte masking key when the mask bit is set.
    REQUIRE( WebSocketImpl::frame_header_remainder( 127, true ) == static_cast< size_t >( 12 ) );
}

TEST_CASE( "frame header remainder for 16-bit extended length", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::frame_header_remainder( 126, false ) == static_cast< size_t >( 2 ) );
    REQUIRE( WebSocketImpl::frame_header_remainder( 126, true ) == static_cast< size_t >( 6 ) );
}

TEST_CASE( "frame header remainder for small payloads", "[web_socket]" )
{
    // No extended length bytes; only the masking key (if present) follows.
    REQUIRE( WebSocketImpl::frame_header_remainder( 0, false ) == static_cast< size_t >( 0 ) );
    REQUIRE( WebSocketImpl::frame_header_remainder( 125, false ) == static_cast< size_t >( 0 ) );
    REQUIRE( WebSocketImpl::frame_header_remainder( 125, true ) == static_cast< size_t >( 4 ) );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
