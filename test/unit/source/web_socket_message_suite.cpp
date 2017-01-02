/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <tuple>

//Project Includes
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::tuple;
using std::make_tuple;

//Project Namespaces
using restbed::WebSocketMessage;

//External Namespaces

TEST_CASE( "validate default instance values", "[web_socket_message]" )
{
    const WebSocketMessage message;
    
    REQUIRE( message.get_mask( ) == 0 );
    REQUIRE( message.get_length( ) == 0 );
    REQUIRE( message.get_extended_length( ) == 0 );
    REQUIRE( message.get_mask_flag( ) == false );
    REQUIRE( message.get_final_frame_flag( ) == true );
    REQUIRE( message.get_reserved_flags( ) == make_tuple( false, false, false ) );
}

TEST_CASE( "validate copy constructor", "[web_socket_message]" )
{
    WebSocketMessage message;
    message.set_mask( 45454 );
    message.set_length( 127 );
    message.set_extended_length( 654 );
    message.set_mask_flag( false );
    message.set_final_frame_flag( false );
    message.set_reserved_flags( true, false, true );
    
    REQUIRE( message.get_mask( ) == 45454 );
    REQUIRE( message.get_length( ) == 127 );
    REQUIRE( message.get_extended_length( ) == 654 );
    REQUIRE( message.get_mask_flag( ) == false );
    REQUIRE( message.get_final_frame_flag( ) == false );
    REQUIRE( message.get_reserved_flags( ) == make_tuple( true, false, true ) );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[web_socket_message]" )
{
    auto message = new WebSocketMessage( );
    
    REQUIRE_NOTHROW( delete message );
}

TEST_CASE( "validate setters modify default values", "[web_socket_message]" )
{
    WebSocketMessage message;
    message.set_mask( 1234567 );
    message.set_length( 125 );
    message.set_extended_length( 654 );
    message.set_mask_flag( false );
    message.set_final_frame_flag( false );
    message.set_reserved_flags( true, true, true );
    
    REQUIRE( message.get_mask( ) == 1234567 );
    REQUIRE( message.get_length( ) == 125 );
    REQUIRE( message.get_extended_length( ) == 654 );
    REQUIRE( message.get_mask_flag( ) == false );
    REQUIRE( message.get_final_frame_flag( ) == false );
    REQUIRE( message.get_reserved_flags( ) == make_tuple( true, true, true ) );
}

TEST_CASE( "validate mask and mask_flag setter logic", "[web_socket_message]" )
{
    WebSocketMessage message;
    message.set_mask( 123424 );
    
    REQUIRE( message.get_mask( ) == 123424 );
    REQUIRE( message.get_mask_flag( ) == true );
}
