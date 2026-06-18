//System Includes
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/detail/web_socket_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::uint64_t;

//Project Namespaces
using restbed::detail::WebSocketImpl;

//External Namespaces

TEST_CASE( "payload length for small ( non-extended ) frames is the length indicator", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length( 0, 0 ) == static_cast< uint64_t >( 0 ) );
    REQUIRE( WebSocketImpl::payload_length( 5, 0 ) == static_cast< uint64_t >( 5 ) );
    REQUIRE( WebSocketImpl::payload_length( 125, 0 ) == static_cast< uint64_t >( 125 ) );
}

TEST_CASE( "payload length for extended frames is the extended length", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length( 126, 200 ) == static_cast< uint64_t >( 200 ) );
    REQUIRE( WebSocketImpl::payload_length( 127, 70000 ) == static_cast< uint64_t >( 70000 ) );
}

TEST_CASE( "an extended-length frame declaring a zero-length payload reads no payload", "[web_socket]" )
{
    // A 126/127 length indicator with an extended length of zero must yield a
    // zero-length payload. The buggy implementation treated the zero extended
    // length as "absent" and fell back to the indicator ( 126 / 127 ), trying
    // to read phantom payload octets.
    REQUIRE( WebSocketImpl::payload_length( 126, 0 ) == static_cast< uint64_t >( 0 ) );
    REQUIRE( WebSocketImpl::payload_length( 127, 0 ) == static_cast< uint64_t >( 0 ) );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
