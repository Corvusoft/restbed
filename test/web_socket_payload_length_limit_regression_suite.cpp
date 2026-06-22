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

TEST_CASE( "small and 16-bit extended payload lengths are always within limit", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length_within_limit( 0, 0 ) == true );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 125, 0 ) == true );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 126, 65535 ) == true );
}

TEST_CASE( "a 64-bit extended length with the most-significant bit clear is within limit", "[web_socket]" )
{
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 65536 ) == true );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0x7FFFFFFFFFFFFFFFULL ) == true );
}

TEST_CASE( "a 64-bit extended length with the most-significant bit set is rejected", "[web_socket]" )
{
    // RFC 6455 5.2: the most significant bit of the 64-bit payload length MUST
    // be 0. Such a frame is malformed and, left unchecked, would drive an
    // unbounded read/allocation.
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0x8000000000000000ULL ) == false );
    REQUIRE( WebSocketImpl::payload_length_within_limit( 127, 0xFFFFFFFFFFFFFFFFULL ) == false );
}

int main( int argc, char* argv[] )
{
    return Catch::Session( ).run( argc, argv );
}
