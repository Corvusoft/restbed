/*
 * Copyright 2013-2026, Corvusoft Ltd, All Rights Reserved.
 *
 * Regression: a malformed/truncated WebSocket frame makes
 * WebSocketManagerImpl::parse() return nullptr. WebSocketImpl must route that
 * to the error handler rather than dereferencing the null message
 * (parse_length_and_mask) or forwarding it to the message handler and
 * re-listening on the socket (parse_payload). The unguarded code crashed.
 */

//System Includes
#include <memory>
#include <system_error>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/web_socket.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>
#include <corvusoft/restbed/detail/web_socket_impl.hpp>
#include <corvusoft/restbed/detail/web_socket_manager_impl.hpp>

//External Includes
#include <catch2/catch_all.hpp>
#include <catch2/catch_session.hpp>

//System Namespaces
using std::byte;
using std::error_code;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces
using restbed::Bytes;
using restbed::WebSocket;
using restbed::WebSocketMessage;
using restbed::detail::WebSocketImpl;
using restbed::detail::WebSocketManagerImpl;

//External Namespaces

// A text frame with the mask bit set but its 4-byte masking key missing.
// WebSocketManagerImpl::parse() rejects it with nullptr. parse_*() assemble the
// packet as packet + data, so { 0x81, 0x80 } + { 0x00 } == { 0x81, 0x80, 0x00 }.
static const Bytes truncated_head { byte{ 0x81 }, byte{ 0x80 } };
static const Bytes truncated_tail { byte{ 0x00 } };

TEST_CASE( "malformed frame in parse_length_and_mask reports error without crashing", "[web_socket]" )
{
    WebSocketImpl impl;
    impl.m_manager = make_shared< WebSocketManagerImpl >( );

    bool error_invoked = false;
    impl.m_error_handler = [ &error_invoked ]( const shared_ptr< WebSocket >, const error_code )
    {
        error_invoked = true;
    };

    impl.parse_length_and_mask( truncated_tail, truncated_head, nullptr );

    REQUIRE( error_invoked );
}

TEST_CASE( "malformed frame in parse_payload reports error and skips the message handler", "[web_socket]" )
{
    WebSocketImpl impl;
    impl.m_manager = make_shared< WebSocketManagerImpl >( );

    bool error_invoked = false;
    bool message_invoked = false;
    impl.m_error_handler = [ &error_invoked ]( const shared_ptr< WebSocket >, const error_code )
    {
        error_invoked = true;
    };
    impl.m_message_handler = [ &message_invoked ]( const shared_ptr< WebSocket >, const shared_ptr< WebSocketMessage > )
    {
        message_invoked = true;
    };

    impl.parse_payload( truncated_tail, truncated_head, nullptr );

    REQUIRE( error_invoked );
    REQUIRE_FALSE( message_invoked );
}

int main( int argc, char* argv[] )
{
    return Catch::Session().run( argc, argv );
}
