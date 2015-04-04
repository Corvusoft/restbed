/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <ctime>
#include <chrono>

//Project Includes
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/detail/response_builder_impl.h"

//External Includes
#include <corvusoft/framework/map>
#include <corvusoft/framework/date>
#include <corvusoft/framework/string>

//System Namespaces
using std::string;
using std::time_t;
using std::multimap;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::chrono::system_clock;

//Project Namespaces
using restbed::Response;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using framework::Map;
using framework::Date;
using framework::Bytes;
using framework::String;

namespace restbed
{
    namespace detail
    {
        void ResponseBuilderImpl::write( const Response& response, const shared_ptr< tcp::socket >& socket )
        {
            string headers = String::format( "%s%s\r\n", generate_status_section( response ).data( ),
                                                         generate_header_section( response ).data( ) );

            asio::write( *socket, buffer( headers ), asio::transfer_exactly( headers.size( ) ) );

            auto callback = response.m_pimpl->get_body_callback( );

            if ( callback )
            {
                Bytes body;

                do
                {
                    body = callback( );
                    asio::write( *socket, buffer( body ), asio::transfer_exactly( body.size( ) ) );
                }
                while ( not body.empty( ) );
            }
            else
            {
                Bytes body = response.get_body( );
                asio::write( *socket, buffer( body ), asio::transfer_exactly( body.size( ) ) );
            }
        }

        ResponseBuilderImpl::ResponseBuilderImpl( void ) : ResponseImpl( )
        {
            return;
        }
        
        ResponseBuilderImpl::ResponseBuilderImpl( const ResponseBuilderImpl& original ) : ResponseImpl( original )
        {
            return;
        }
        
        ResponseBuilderImpl::~ResponseBuilderImpl( void )
        {
            return;
        }

        string ResponseBuilderImpl::generate_status_section( const Response& response )
        {
            string status_message = response.get_status_message( );

            return String::format( "HTTP/%.1f %i %s\r\n", response.get_version( ),
                                                          response.get_status_code( ),
                                                          response.get_status_message( ).data( ) );
        }

        string ResponseBuilderImpl::generate_header_section( const Response& response )
        {
            string section = generate_default_date_header( response );
            section += generate_default_connection_header( response );
            section += generate_default_server_header( response );
            section += generate_default_content_type_header( response );
            section += generate_default_content_length_header( response );

            for ( auto header : response.get_headers( ) )
            {
                section += String::format( "%s: %s\r\n", header.first.data( ), header.second.data( ) );
            }

            return section;
        }

        string ResponseBuilderImpl::generate_default_date_header( const Response& response )
        {
            string header = String::empty;

            if ( not response.m_pimpl->has_header( "Date" ) )
            {
                string date = Date::format( system_clock::now( ) );

                header = String::format( "Date: %s\r\n", date.data( ) );
            }

            return header;
        }

        string ResponseBuilderImpl::generate_default_server_header( const Response& response )
        {
            string header = String::empty;

            if ( not response.m_pimpl->has_header( "Server" ) )
            {
                header = "Server: Corvusoft - restbed\r\n";
            }

            return header;
        }

        string ResponseBuilderImpl::generate_default_connection_header( const Response& response )
        {
            string header = String::empty;

            if ( not response.m_pimpl->has_header( "Connection" ) )
            {
                header = "Connection: close\r\n";
            }

            return header;
        }

        string ResponseBuilderImpl::generate_default_content_type_header( const Response& response )
        {
            string header = String::empty;

            if ( not response.m_pimpl->has_header( "Content-Type" ) and not response.get_body( ).empty( ) )
            {
                header = "Content-Type: text/plain; charset=us-ascii\r\n";
            }

            return header;
        }

        string ResponseBuilderImpl::generate_default_content_length_header( const Response& response )
        {
            string header = String::empty;

            if ( not response.m_pimpl->has_header( "Transfer-Encoding" ) and
                 not response.m_pimpl->has_header( "Content-Length" ) and
                 not response.get_body( ).empty( ) )
            {
                header = String::format( "Content-Length: %i\r\n", response.get_body( ).size( ) );
            }

            return header;
        }

        ResponseBuilderImpl& ResponseBuilderImpl::operator =( const ResponseBuilderImpl& value )
        {
            *this = value;
            
            return *this;
        }
    }
}
