/*
 * Example illustrating web socket server.
 *
 * Server Usage:
 *    ./distribution/example/web_socket
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/socket'
 */

#include <string>
#include <cstring>
#include <memory>
#include <utility>
#include <cstdlib>
#include <restbed>
#include <system_error>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

using namespace std;
using namespace restbed;

string base64_encode( const unsigned char* input, int length )
{
    BIO* bmem, *b64;
    BUF_MEM* bptr;

    b64 = BIO_new( BIO_f_base64( ) );
    bmem = BIO_new( BIO_s_mem( ) );
    b64 = BIO_push( b64, bmem );
    BIO_write( b64, input, length );
    BIO_flush( b64 );
    BIO_get_mem_ptr( b64, &bptr );

    char* buff = ( char* )malloc( bptr->length );
    memcpy( buff, bptr->data, bptr->length - 1 );
    buff[ bptr->length - 1 ] = 0;

    BIO_free_all( b64 );

    return buff;
}

void close_handler( const shared_ptr< WebSocket > )
{
    fprintf( stderr, "WebSocket Closed\n" );
}

void error_handler( const shared_ptr< WebSocket >, const error_code error )
{
    fprintf( stderr, "WebSocket Errored: %s\n", error.message( ).data( ) );
}

void message_handler( const shared_ptr< WebSocket > socket, const shared_ptr< WebSocketMessage > message )
{
    const auto data = String::format( "WebSocket Message: %.*s\n", message->get_data( ).size( ), message->get_data( ).data( ) );

    // auto flags = message->get_reserved_flags( );
    // fprintf( stderr, "Final Frame Flag: %d\n", message->get_final_frame_flag( ) );
    // fprintf( stderr, "Reserved Flags: %d %d %d\n", std::get<0>( flags ), std::get<1>( flags ), std::get<2>( flags ) );
    // fprintf( stderr, "OpCode: %d\n", message->get_opcode( ) );
    // fprintf( stderr, "Mask Flag %d\n", message->get_mask_flag( ) );
    // fprintf( stderr, "Payload Length %d\n", message->get_payload_length( ) );
    // fprintf( stderr, "Masking Key %u\n", message->get_mask( ) );

    fprintf( stderr, "%s", data.data( ) );
}

void get_method_handler( const shared_ptr< Session > session )
{
    auto request = session->get_request( );

    //if ( request->get_header( "connection", String::lowercase ) == "upgrade" ) //keep-alive, upgrade
    //{
    //if ( request->get_header( "upgrade", String::lowercase ) == "websocket" )
    //{
    std::string body = ""; //remove me.

    auto key = request->get_header( "Sec-WebSocket-Key" );
    key.append( "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" );

    Byte hash[ SHA_DIGEST_LENGTH ];
    SHA1( reinterpret_cast< const unsigned char* >( key.data( ) ), key.length( ), hash );

    multimap< string, string > headers;
    headers.insert( make_pair( "Upgrade", "websocket" ) );
    headers.insert( make_pair( "Connection", "Upgrade" ) );
    headers.insert( make_pair( "Sec-WebSocket-Accept", base64_encode( hash, SHA_DIGEST_LENGTH ) ) );

    session->upgrade( SWITCHING_PROTOCOLS, body, headers, [ ]( const shared_ptr< WebSocket > socket )
    {
        if ( socket->is_open( ) )
        {
            socket->set_close_handler( close_handler );
            socket->set_error_handler( error_handler );
            socket->set_message_handler( message_handler );

            auto message = make_shared< WebSocketMessage >( WebSocketMessage::TEXT_FRAME, "Message from server" );

            socket->send( message, [ ]( const shared_ptr< WebSocket > )
            {
                fprintf( stderr, "WebSocket sent welcome message.\n" );
            } );
        }
        else
        {
            fprintf( stderr, "Client closed connection, WebSocket negotiation failed.\n" );
        }
    } );

    return;
    //}
    //}

    //session->close( BAD_REQUEST );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/socket" );
    resource->set_method_handler( "GET", get_method_handler );

    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );

    Service service;
    service.publish( resource );
    service.start( settings );

    return EXIT_SUCCESS;
}
