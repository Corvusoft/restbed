/*
 * Example illustrating web socket server.
 *
 * Server Usage:
 *    ./distribution/example/web_socket
 *
 * Client Usage:
 *    curl -w'\n' -v -X GET 'http://localhost:1984/socket'
 *
 * Further Reading:
 *
 */

#include <map>
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

shared_ptr< Service > service = nullptr;

map< string, shared_ptr< WebSocket > > sockets = { };

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

void close_handler( const shared_ptr< WebSocket > socket )
{
    const auto key = socket->get_key( );
    sockets.erase( key );
    
    fprintf( stderr, "Closed connection to %s.\n", key.data( ) );
}

void error_handler( const shared_ptr< WebSocket > socket, const error_code error )
{
    const auto key = socket->get_key( );
    fprintf( stderr, "WebSocket Errored '%s' for %s.\n", error.message( ).data( ), key.data( ) );
}

// void ping_handler( void )
// {
//     for ( auto entry : sockets )
//     {
//         auto socket = entry->second;

//         //send ping
//     }

//     //service->schedule( )
// }

void message_handler( const shared_ptr< WebSocket > source, const shared_ptr< WebSocketMessage > message )
{
    //if ( message is ping ) send pong. //ignore pongs
    
    const auto source_key = source->get_key( );
    const auto data = String::format( "Received message '%.*s' from %s\n", message->get_data( ).size( ), message->get_data( ).data( ), source_key.data( ) );
    fprintf( stderr, "%s", data.data( ) );
    
    for ( auto socket : sockets )
    {
        auto destination_key = socket.first;
        
        if ( source_key not_eq destination_key )
        {
            auto destination = socket.second;
            destination->send( message );
        }
        
    }
    
    // auto flags = message->get_reserved_flags( );
    // fprintf( stderr, "Final Frame Flag: %d\n", message->get_final_frame_flag( ) );
    // fprintf( stderr, "Reserved Flags: %d %d %d\n", std::get<0>( flags ), std::get<1>( flags ), std::get<2>( flags ) );
    // fprintf( stderr, "OpCode: %d\n", message->get_opcode( ) );
    // fprintf( stderr, "Mask Flag %d\n", message->get_mask_flag( ) );
    // fprintf( stderr, "Payload Length %d\n", message->get_payload_length( ) );
    // fprintf( stderr, "Masking Key %u\n", message->get_mask( ) );
}

void get_method_handler( const shared_ptr< Session > session )
{
    auto request = session->get_request( );
    
    //if ( request->get_header( "connection", String::lowercase ) == "upgrade" ) //keep-alive, upgrade
    //{
    //if ( request->get_header( "upgrade", String::lowercase ) == "websocket" )
    //{
    auto key = request->get_header( "Sec-WebSocket-Key" );
    key.append( "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" );
    
    Byte hash[ SHA_DIGEST_LENGTH ];
    SHA1( reinterpret_cast< const unsigned char* >( key.data( ) ), key.length( ), hash );
    
    multimap< string, string > headers;
    headers.insert( make_pair( "Upgrade", "websocket" ) );
    headers.insert( make_pair( "Connection", "Upgrade" ) );
    headers.insert( make_pair( "Sec-WebSocket-Accept", base64_encode( hash, SHA_DIGEST_LENGTH ) ) );
    
    session->upgrade( SWITCHING_PROTOCOLS, headers, [ ]( const shared_ptr< WebSocket > socket )
    {
        if ( socket->is_open( ) )
        {
            socket->set_close_handler( close_handler );
            socket->set_error_handler( error_handler );
            socket->set_message_handler( message_handler );
            
            auto message = make_shared< WebSocketMessage >( WebSocketMessage::TEXT_FRAME, "Welcome to Corvusoft Chat!" );
            
            socket->send( message, [ ]( const shared_ptr< WebSocket > socket )
            {
                const auto key = socket->get_key( );
                sockets.insert( make_pair( key, socket ) );
                
                fprintf( stderr, "Sent welcome message to %s.\n", key.data( ) );
            } );
        }
        else
        {
            fprintf( stderr, "WebSocket Negotiation Failed: Client closed connection.\n" );
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
    resource->set_path( "/socket" ); ///chat
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    service = make_shared< Service >( );
    service->publish( resource );
    //service->schedule( ping_handler, seconds( 4000 ) );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
