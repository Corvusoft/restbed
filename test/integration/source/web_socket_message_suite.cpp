/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <tuple>
#include <string>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/string.hpp>
#include <corvusoft/restbed/web_socket_message.hpp>

//External Includes
#include <catch.hpp>

//System Namespaces
using std::tuple;
using std::string;
using std::make_tuple;

//Project Namespaces
using restbed::Bytes;
using restbed::String;
using restbed::WebSocketMessage;

//External Namespaces

TEST_CASE( "validate default instance values", "[web_socket_message]" )
{
    const WebSocketMessage opcode_and_byte( WebSocketMessage::OpCode::TEXT_FRAME, String::to_bytes( "test" ) );
    REQUIRE( opcode_and_byte.get_mask( ) == 0 );
    REQUIRE( opcode_and_byte.get_length( ) == 4 );
    REQUIRE( opcode_and_byte.get_extended_length( ) == 0 );
    REQUIRE( opcode_and_byte.get_mask_flag( ) == false );
    REQUIRE( opcode_and_byte.get_final_frame_flag( ) == true );
    REQUIRE( opcode_and_byte.get_data( ) == String::to_bytes( "test" ) );
    REQUIRE( opcode_and_byte.get_reserved_flags( ) == make_tuple( false, false, false ) );
    REQUIRE( opcode_and_byte.get_opcode( ) == WebSocketMessage::OpCode::TEXT_FRAME );
    
    const WebSocketMessage opcode_and_string( WebSocketMessage::OpCode::CONNECTION_CLOSE_FRAME, "Hello, World!" );
    REQUIRE( opcode_and_string.get_mask( ) == 0 );
    REQUIRE( opcode_and_string.get_length( ) == 13 );
    REQUIRE( opcode_and_string.get_extended_length( ) == 0 );
    REQUIRE( opcode_and_string.get_mask_flag( ) == false );
    REQUIRE( opcode_and_string.get_final_frame_flag( ) == true );
    REQUIRE( opcode_and_string.get_data( ) == String::to_bytes( "Hello, World!" ) );
    REQUIRE( opcode_and_string.get_reserved_flags( ) == make_tuple( false, false, false ) );
    REQUIRE( opcode_and_string.get_opcode( ) == WebSocketMessage::OpCode::CONNECTION_CLOSE_FRAME );
    
    const WebSocketMessage opcode_and_byte_and_mask( WebSocketMessage::OpCode::PING_FRAME, String::to_bytes( "C" ), 5655432 );
    REQUIRE( opcode_and_byte_and_mask.get_mask( ) == 5655432 );
    REQUIRE( opcode_and_byte_and_mask.get_length( ) == 1 );
    REQUIRE( opcode_and_byte_and_mask.get_extended_length( ) == 0 );
    REQUIRE( opcode_and_byte_and_mask.get_mask_flag( ) == true );
    REQUIRE( opcode_and_byte_and_mask.get_final_frame_flag( ) == true );
    REQUIRE( opcode_and_byte_and_mask.get_data( ) == String::to_bytes( "C" ) );
    REQUIRE( opcode_and_byte_and_mask.get_reserved_flags( ) == make_tuple( false, false, false ) );
    REQUIRE( opcode_and_byte_and_mask.get_opcode( ) == WebSocketMessage::OpCode::PING_FRAME );
    
    const WebSocketMessage opcode_and_string_and_mask( WebSocketMessage::OpCode::PONG_FRAME, "Corvusoft", 123456789 );
    REQUIRE( opcode_and_string_and_mask.get_mask( ) == 123456789 );
    REQUIRE( opcode_and_string_and_mask.get_length( ) == 9 );
    REQUIRE( opcode_and_string_and_mask.get_extended_length( ) == 0 );
    REQUIRE( opcode_and_string_and_mask.get_mask_flag( ) == true );
    REQUIRE( opcode_and_string_and_mask.get_final_frame_flag( ) == true );
    REQUIRE( opcode_and_string_and_mask.get_data( ) == String::to_bytes( "Corvusoft" ) );
    REQUIRE( opcode_and_string_and_mask.get_reserved_flags( ) == make_tuple( false, false, false ) );
    REQUIRE( opcode_and_string_and_mask.get_opcode( ) == WebSocketMessage::OpCode::PONG_FRAME );
}

TEST_CASE( "validate copy constructor", "[web_socket_message]" )
{
    const WebSocketMessage message( WebSocketMessage::OpCode::TEXT_FRAME );
    
    REQUIRE( message.get_opcode( ) == WebSocketMessage::OpCode::TEXT_FRAME );
}

TEST_CASE( "confirm default destructor throws no exceptions", "[web_socket_message]" )
{
    auto message = new WebSocketMessage( );
    
    REQUIRE_NOTHROW( delete message );
}

TEST_CASE( "validate setters modify default values", "[web_socket_message]" )
{
    WebSocketMessage message;
    message.set_data( String::to_bytes( "Test data." ) );
    message.set_opcode( WebSocketMessage::OpCode::CONTINUATION_FRAME );
    
    REQUIRE( message.get_data( ) == String::to_bytes( "Test data." ) );
    REQUIRE( message.get_opcode( ) == WebSocketMessage::OpCode::CONTINUATION_FRAME );
}

TEST_CASE( "validate length and extended length are correctly set", "[web_socket_message]" )
{
    string upper_limit_data( 125, 'a' );
    WebSocketMessage upper_limit( WebSocketMessage::OpCode::TEXT_FRAME, upper_limit_data );
    REQUIRE( upper_limit.get_length( ) == 125 );
    REQUIRE( upper_limit.get_extended_length( ) == 0 );
    
    string upper_limit_exceeded_data( 126, 'x' );
    WebSocketMessage upper_limit_exceeded( WebSocketMessage::OpCode::TEXT_FRAME, upper_limit_exceeded_data );
    REQUIRE( upper_limit_exceeded.get_length( ) == 126 );
    REQUIRE( upper_limit_exceeded.get_extended_length( ) == 126 );
    
    string upper_extend_limit_data( 65534, 's' );
    WebSocketMessage upper_extend_limit( WebSocketMessage::OpCode::TEXT_FRAME, upper_extend_limit_data );
    REQUIRE( upper_extend_limit.get_length( ) == 126 );
    REQUIRE( upper_extend_limit.get_extended_length( ) == 65534 );
    
    string upper_extend_limit_exceeded_data( 65535, 'Y' );
    WebSocketMessage upper_extend_limit_exceeded( WebSocketMessage::OpCode::TEXT_FRAME, upper_extend_limit_exceeded_data );
    REQUIRE( upper_extend_limit_exceeded.get_length( ) == 127 );
    REQUIRE( upper_extend_limit_exceeded.get_extended_length( ) == 65535 );
}
