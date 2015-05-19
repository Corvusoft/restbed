/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <istream>
#include <iostream> //debug

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::ssub_match;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::error_code;
using framework::String;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_id( String::empty ),
            m_buffer( nullptr ),
            m_socket( nullptr )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }

        void SessionImpl::fetch( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session )
        {
            m_buffer = make_shared< asio::streambuf >( );

            asio::async_read_until( *m_socket,
                                    *m_buffer,
                                    "\r\n\r\n",
                                    bind( &SessionImpl::parse_status_and_headers, this, callback, session, _1 ) );
        }

        const string& SessionImpl::get_id( void ) const
        {
            return m_id;
        }

        void SessionImpl::set_id( const string& value )
        {
            m_id = value;
        }

        void SessionImpl::set_socket( const std::shared_ptr< tcp::socket >& value )
        {
            m_socket = value; //just pass this in via fetch?
        }

        void SessionImpl::parse_status_and_headers( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session, const asio::error_code& error )
        {
            //if ( error )
            //{
            //    throw asio::system_error( code );
            //}

            istream stream( m_buffer.get( ) );

            string data = String::empty;
            getline( stream, data );

            smatch base_matches;
            static const regex status_pattern( "^(.*) (.*) (HTTP\\/[0-9]\\.[0-9])\\s*$" ); //class wide?
            const bool match = regex_match( data, base_matches, status_pattern );

            if ( not match or base_matches.size( ) not_eq 4 )
            {
                std::cout << "FAILED BAD REQUEST!" << base_matches.size( ) << std::endl;
            }

            string method = base_matches[ 1 ].str( );
            string path = base_matches[ 2 ].str( );
            string version = base_matches[ 3 ].str( );

            std::cout << "method: " << method << std::endl;
            std::cout << "path: " << path << std::endl;
            std::cout << "version: " << version << std::endl;

            getline( stream, data );
            while ( not stream.eof( ) and data not_eq "\r" )
            {
                static const regex header_pattern( "^(.*): *(.*)\\s*$" );
                const bool match2 = regex_match( data, base_matches, header_pattern );

                if ( not match2 or base_matches.size( ) not_eq 3 )
                {
                    std::cout << "FAILED BAD REQUEST!" << base_matches.size( ) << std::endl;
                }

                string name = base_matches[ 1 ].str( );
                string value = base_matches[ 2 ].str( );

                std::cout << name << ": " << value << std::endl;
                getline( stream, data );
            }

            callback( session );
        }
    }
}
