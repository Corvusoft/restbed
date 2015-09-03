/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_HTTP_H
#define _RESTBED_HTTP_H 1

//System Includes
#include <map>
#include <string>
#include <cstdint>
#include <iterator>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/byte.hpp"
#include "corvusoft/restbed/string.hpp"

//External Includes
#include <asio.hpp>

//System Namespaces
using std::stoi;
using std::stod;
using std::string;
using std::istream;
using std::ostream;
using std::multimap;
using std::to_string;
using std::runtime_error;
using std::istreambuf_iterator;

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Delcarations
    
    class Http
    {
        public:
            //Friends
            
            //Definitions
            struct Request
            {
                Bytes body = { };
                uint16_t port = 80;
                double version = 1.1;
                std::string host = "";
                std::string path = "/";
                std::string method = "GET";
                std::multimap< std::string, std::string > headers { };
            };
            
            struct Response
            {
                Bytes body = { };
                double version = 1.1;
                int status_code = 0;
                std::string status_message = "";
                std::multimap< std::string, std::string > headers { };
            };
            
            //Constructors
            
            //Functionality
            static Response get( const Request& request )
            {
                return perform( "GET", request );
            }
            
            static Response put( const Request& request )
            {
                return perform( "PUT", request );
            }
            
            static Response trace( const Request& request )
            {
                return perform( "TRACE", request );
            }
            
            static Response post( const Request& request )
            {
                return perform( "POST", request );
            }
            
            static Response head( const Request& request )
            {
                return perform( "HEAD", request );
            }
            
            static Response patch( const Request& request )
            {
                return perform( "PATCH", request );
            }
            
            static Response destroy( const Request& request )
            {
                return perform( "DELETE", request );
            }
            
            static Response connect( const Request& request )
            {
                return perform( "CONNECT", request );
            }
            
            static Response options( const Request& request )
            {
                return perform( "OPTIONS", request );
            }
            
            static Response perform( const Request& request )
            {
                return perform( request.method, request );
            }
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            Http( void ) = delete;
            
            Http( const Http& original ) = delete;
            
            virtual ~Http( void ) = delete;
            
            //Functionality
            static Response perform( const string& method, const Request& request )
            {
                asio::io_service io_service;
                asio::ip::tcp::resolver resolver( io_service );
                asio::ip::tcp::resolver::query query( request.host, ::to_string( request.port ) );
                asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve( query );
                asio::ip::tcp::resolver::iterator end;
                
                asio::ip::tcp::socket socket( io_service );
                asio::error_code error = asio::error::host_not_found;
                
                while ( error and endpoint_iterator not_eq end )
                {
                    socket.close( );
                    socket.connect( *endpoint_iterator++, error );
                }
                
                if ( error )
                {
                    throw asio::system_error( error );
                }
                
                asio::streambuf request_buffer;
                ostream request_stream( &request_buffer );
                
                request_stream << String::uppercase( method ) << " " << request.path << " HTTP/1.1\r\n";
                request_stream << "Host: " << request.host << "\r\n";
                request_stream << "Connection: close\r\n";
                
                for ( auto header : request.headers )
                {
                    request_stream << header.first << ": " << header.second << "\r\n";
                }
                
                request_stream << "\r\n";
                
                if ( not request.body.empty( ) )
                {
                    request_stream << request.body.data( );
                }
                
                asio::write( socket, request_buffer );
                
                Response response;
                asio::streambuf response_buffer;
                asio::read_until( socket, response_buffer, "\r\n" );
                istream response_stream( &response_buffer );
                
                string status;
                getline( response_stream, status );
                auto status_line = String::split( status, ' ' );
                
                string http_version = status_line[ 0 ].substr( status_line[ 0 ].find_first_of( '/' ) + 1 );
                response.version = stod( http_version );
                
                response.status_code = stoi( status_line[ 1 ] );
                response.status_message = status_line[ 2 ].substr( 0, status_line[ 2 ].length( ) - 1 );
                
                asio::read_until( socket, response_buffer, "\r\n\r\n", error );
                
                string header = "";
                
                while ( getline( response_stream, header ) and header not_eq "\r" )
                {
                    auto name_value = String::split( header, ':' );
                    auto name = name_value[ 0 ];
                    auto value = name_value[ 1 ].substr( 1, name_value[ 1 ].find_last_not_of( "\r\n" ) );
                    response.headers.insert( make_pair( name, value ) );
                }
                
                while ( not error )
                {
                    auto body = Bytes( istreambuf_iterator< char >( &response_buffer ), istreambuf_iterator< char >( ) );
                    response_buffer.consume( body.size( ) );
                    response.body.insert( response.body.end( ), body.begin( ), body.end( ) );
                    
                    asio::read( socket, response_buffer, asio::transfer_all( ), error );
                }
                
                if ( error not_eq asio::error::eof )
                {
                    throw runtime_error( "failed to read response." );
                }
                
                return response;
            }
            
            //Getters
            
            //Setters
            
            //Operators
            Http& operator =( const Http& value ) = delete;
    };
}

#endif  /* _RESTBED_HTTP_H */

