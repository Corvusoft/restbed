/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <stdexcept>
#include <iostream> //debug

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::multimap;
using std::make_pair;
using std::ssub_match;
using std::shared_ptr;
using std::make_shared;
using std::regex_match;
using std::runtime_error;
using std::placeholders::_1;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::ip::tcp;
using asio::error_code;
using framework::Uri;
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
                                    bind( &SessionImpl::parse_request, this, callback, session, _1 ) );
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
            m_socket = value;
        }

        const multimap< string, string > SessionImpl::parse_headers( istream& stream )
        {
            smatch matches;
            string data = String::empty;
            multimap< string, string > headers;
            static const regex pattern( "^(.*): *(.*)\\s*$" );

            while ( getline( stream, data ) and data not_eq "\r" )
            {
                if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 3 )
                {
                    throw runtime_error( "FAILED BAD REQUEST!" );
                }

                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }

            return headers;
        }

        const map< string, string > SessionImpl::parse_status_path_and_version( istream& stream )
        {
            string data = String::empty;
            getline( stream, data );

            smatch matches;
            static const regex pattern( "^(.*) (.*) (HTTP\\/[0-9]\\.[0-9])\\s*$" );

            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "FAILED BAD REQUEST!" );
            }

            const string version = matches[ 3 ].str( );

            return map< string, string > {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", version.substr( version.find_first_of( "HTTP/" ) ) }
            };
        }

        void SessionImpl::parse_request( const function< void ( const shared_ptr< Session >& ) >& callback, const std::shared_ptr< Session >& session, const asio::error_code& error )
        {
            if ( error )
            {
                throw runtime_error( "" ); //throw asio::system_error( code );
            }

            istream stream( m_buffer.get( ) );
            const auto items = parse_status_path_and_version( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );

            auto request = RequestBuilderImpl::build( stream );
            session = SessionBuilderImpl::modifiy( session, request );

            callback( session );
        }
    }
}
