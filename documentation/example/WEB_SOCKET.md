Overview
--------

"WebSocket is a computer communications protocol, providing full-duplex communication channels over a single TCP connection. The WebSocket protocol was standardized by the IETF as RFC 6455 in 2011, and the WebSocket API in Web IDL is being standardized by the W3C. WebSocket is a different TCP protocol from HTTP." -- [Wikipedia](https://en.wikipedia.org/wiki/WebSocket)

Example
-------

```C++
#include <map>
#include <chrono>
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
using namespace std::chrono;

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
    ( void ) BIO_flush( b64 );
    BIO_get_mem_ptr( b64, &bptr );
    
    char* buff = ( char* )malloc( bptr->length );
    memcpy( buff, bptr->data, bptr->length - 1 );
    buff[ bptr->length - 1 ] = 0;
    
    BIO_free_all( b64 );
    
    return buff;
}

multimap< string, string > build_websocket_handshake_response_headers( const shared_ptr< const Request >& request )
{
    auto key = request->get_header( "Sec-WebSocket-Key" );
    key.append( "258EAFA5-E914-47DA-95CA-C5AB0DC85B11" );
    
    Byte hash[ SHA_DIGEST_LENGTH ];
    SHA1( reinterpret_cast< const unsigned char* >( key.data( ) ), key.length( ), hash );
    
    multimap< string, string > headers;
    headers.insert( make_pair( "Upgrade", "websocket" ) );
    headers.insert( make_pair( "Connection", "Upgrade" ) );
    headers.insert( make_pair( "Sec-WebSocket-Accept", base64_encode( hash, SHA_DIGEST_LENGTH ) ) );
    
    return headers;
}

void ping_handler( void )
{
    for ( auto entry : sockets )
    {
        auto key = entry.first;
        auto socket = entry.second;
        
        if ( socket->is_open( ) )
        {
            socket->send( WebSocketMessage::PING_FRAME );
        }
        else
        {
            socket->close( );
        }
    }
}

void close_handler( const shared_ptr< WebSocket > socket )
{
    if ( socket->is_open( ) )
    {
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::CONNECTION_CLOSE_FRAME, Bytes( { 10, 00 } ) );
        socket->send( response );
    }
    
    const auto key = socket->get_key( );
    sockets.erase( key );
    
    fprintf( stderr, "Closed connection to %s.\n", key.data( ) );
}

void error_handler( const shared_ptr< WebSocket > socket, const error_code error )
{
    const auto key = socket->get_key( );
    fprintf( stderr, "WebSocket Errored '%s' for %s.\n", error.message( ).data( ), key.data( ) );
}

void message_handler( const shared_ptr< WebSocket > source, const shared_ptr< WebSocketMessage > message )
{
    const auto opcode = message->get_opcode( );
    
    if ( opcode == WebSocketMessage::PING_FRAME )
    {
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::PONG_FRAME, message->get_data( ) );
        source->send( response );
    }
    else if ( opcode == WebSocketMessage::PONG_FRAME )
    {
        //Ignore PONG_FRAME.
        //
        //Every time the ping_handler is scheduled to run, it fires off a PING_FRAME to each
        //WebSocket. The client, if behaving correctly, will respond with a PONG_FRAME.
        //
        //On each occasion the underlying TCP socket sees any packet data transfer, whether
        //a PING, PONG, TEXT, or BINARY... frame. It will automatically reset the timeout counter
        //leaving the connection active; see also Settings::set_connection_timeout.
        return;
    }
    else if ( opcode == WebSocketMessage::CONNECTION_CLOSE_FRAME )
    {
        source->close( );
    }
    else if ( opcode == WebSocketMessage::BINARY_FRAME )
    {
        //We don't support binary data.
        auto response = make_shared< WebSocketMessage >( WebSocketMessage::CONNECTION_CLOSE_FRAME, Bytes( { 10, 03 } ) );
        source->send( response );
    }
    else if ( opcode == WebSocketMessage::TEXT_FRAME )
    {
        auto response = make_shared< WebSocketMessage >( *message );
        response->set_mask( 0 );
        
        for ( auto socket : sockets )
        {
            auto destination = socket.second;
            destination->send( response );
        }
        
        const auto key = source->get_key( );
        const auto data = String::format( "Received message '%.*s' from %s\n", message->get_data( ).size( ), message->get_data( ).data( ), key.data( ) );
        fprintf( stderr, "%s", data.data( ) );
    }
}

void get_method_handler( const shared_ptr< Session > session )
{
    const auto request = session->get_request( );
    const auto connection_header = request->get_header( "connection", String::lowercase );
    
    if ( connection_header.find( "upgrade" ) not_eq string::npos )
    {
        if ( request->get_header( "upgrade", String::lowercase ) == "websocket" )
        {
            const auto headers = build_websocket_handshake_response_headers( request );
            
            session->upgrade( SWITCHING_PROTOCOLS, headers, [ ]( const shared_ptr< WebSocket > socket )
            {
                if ( socket->is_open( ) )
                {
                    socket->set_close_handler( close_handler );
                    socket->set_error_handler( error_handler );
                    socket->set_message_handler( message_handler );
                    
                    socket->send( "Welcome to Corvusoft Chat!", [ ]( const shared_ptr< WebSocket > socket )
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
        }
    }
    
    session->close( BAD_REQUEST );
}

int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/chat" );
    resource->set_method_handler( "GET", get_method_handler );
    
    auto settings = make_shared< Settings >( );
    settings->set_port( 1984 );
    
    service = make_shared< Service >( );
    service->publish( resource );
    service->schedule( ping_handler, milliseconds( 5000 ) );
    service->start( settings );
    
    return EXIT_SUCCESS;
}
```

Build
-----

> $ clang++ -o example example.cpp -l restbed -l ssl -l crypt

Execution
---------

> $ ./example

Client
------
```HTML
<!DOCTYPE HTML>
<html>
  <head>
    <style>
      html, body {
        margin: 0;
      }

      ul {
        list-style: none;
      }

      li {
         text-align: left;
      }

      input {
        width: 40%;
        height: 40px;
        line-height: 40px;
        margin-bottom: 10px;
      }

      a {
        margin: 10px;
      }

      .disabled {
        color: #000;
        pointer-events: none;
      }

      #controls {
        width: 100%;
        bottom: 10%;
        position: absolute;
        text-align: center;
      }
    </style>
    <script type="text/javascript">
      function on_return_submit( evt )
      {
         if ( window.restbed.ws === null || window.restbed.ws.readyState !== window.restbed.ws.OPEN )
         {
            return;
         }

         if( evt && evt.keyCode == 13 )
         {
            var message = document.getElementById( "message" );
            window.restbed.ws.send( message.value );

            message.value = "";
         }
      }

      function toggle_control_access( )
      {
         var open = document.getElementById( "open" );
         open.disabled = !open.disabled;

         var message = document.getElementById( "message" );
         message.disabled = !message.disabled;

         var close = document.getElementById( "close" );
         close.className = ( close.className === "disabled" ) ? "" : "disabled";
      }

      function add_message( message )
      {
         var li = document.createElement( "li" );
         li.appendChild( document.createTextNode( "> " + message ) );

         var ul = document.getElementById( "messages" );
         ul.appendChild( li );
      }

      function open( )
      {
         if ( "WebSocket" in window )
         {
            var ws = new WebSocket( "ws://localhost:1984/chat" );

            ws.onopen = function( )
            {
               add_message( "Established connection." );

               toggle_control_access( );
            };

            ws.onmessage = function( evt )
            {
               add_message( evt.data );
            };

            ws.onclose = function( evt )
            {
               add_message( "Connection closed with RFC6455 code " + evt.code + "." );

               toggle_control_access( );
            };

            ws.onerror = function( evt )
            {
               add_message( "Error: socket connection interrupted." );
            };

            window.restbed.ws = ws;
         }
         else
         {
            alert( "WebSockets NOT supported by your Browser!" );
         }
      }

      function close( )
      {
         window.restbed.ws.close( );
      }

      ( function( )
      {
         window.restbed = { ws: null };
      } )( );
    </script>
  </head>
  <body>
     <div>
       <ul id="messages"></ul>
       <div id="controls">
         <input id="message" type="text" onKeyPress="return on_return_submit( event )" disabled/>
         <div>
           <a id="open" href="javascript:open( )">Open Chat</a>
           <a id="close" href="javascript:close( )" class="disabled">Close Chat</a>
         <div>
       </div>
     </div>
  </body>
</html>
```
