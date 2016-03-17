/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <regex>
#include <utility>
#include <ciso646>
#include <stdexcept>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
#include "corvusoft/restbed/http.hpp"
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/context_value.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::set;
using std::regex;
using std::smatch;
using std::string;
using std::getline;
using std::istream;
using std::function;
using std::multimap;
using std::make_pair;
using std::exception;
using std::to_string;
using std::ssub_match;
using std::shared_ptr;
using std::error_code;
using std::make_shared;
using std::regex_match;
using std::regex_error;
using std::runtime_error;
using std::placeholders::_1;
using std::rethrow_exception;
using std::current_exception;
using std::chrono::milliseconds;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::streambuf;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : m_id( String::empty ),
            m_request( nullptr ),
            m_resource( nullptr ),
            m_settings( nullptr ),
            m_manager( nullptr ),
            m_headers( ),
            m_context( ),
            m_router( nullptr ),
            m_error_handler( nullptr )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }
        
        void SessionImpl::fetch( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
        {
            session->m_pimpl->m_request->m_pimpl->m_buffer = make_shared< asio::streambuf >( );
            
            m_request->m_pimpl->m_socket->read( session->m_pimpl->m_request->m_pimpl->m_buffer, "\r\n\r\n", bind( &SessionImpl::parse_request, this, _1, session, callback ) );
        }
        
        void SessionImpl::fetch_body( const size_t length, const shared_ptr< Session > session, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback ) const
        {
            const auto data_ptr = asio::buffer_cast< const Byte* >( session->m_pimpl->m_request->m_pimpl->m_buffer->data( ) );
            const auto data = Bytes( data_ptr, data_ptr + length );
            session->m_pimpl->m_request->m_pimpl->m_buffer->consume( length );
            
            auto& body = m_request->m_pimpl->m_body;
            
            if ( body.empty( ) )
            {
                body = data;
            }
            else
            {
                body.insert( body.end( ), data.begin( ), data.end( ) );
            }
            
            callback( session, data );
        }
        
        void SessionImpl::transmit( const Response& response, const function< void ( const error_code&, size_t ) >& callback ) const
        {
            auto hdrs = m_settings->get_default_headers( );
            
            if ( m_resource not_eq nullptr )
            {
                const auto m_resource_headers = m_resource->m_pimpl->m_default_headers;
                hdrs.insert( m_resource_headers.begin( ), m_resource_headers.end( ) );
            }
            
            hdrs.insert( m_headers.begin( ), m_headers.end( ) );
            
            auto response_headers = response.get_headers( );
            hdrs.insert( response_headers.begin( ), response_headers.end( ) );
            
            auto payload = make_shared< Response >( );
            payload->set_headers( hdrs );
            payload->set_body( response.get_body( ) );
            payload->set_version( response.get_version( ) );
            payload->set_protocol( response.get_protocol( ) );
            payload->set_status_code( response.get_status_code( ) );
            payload->set_status_message( response.get_status_message( ) );
            
            if ( payload->get_status_message( ).empty( ) )
            {
                payload->set_status_message( m_settings->get_status_message( payload->get_status_code( ) ) );
            }
            
            m_request->m_pimpl->m_socket->write( Http::to_bytes( payload ), callback );
        }
        
        const map< string, string > SessionImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^([0-9a-zA-Z]*) ([a-zA-Z0-9:@_~!,;=#%&'\\-\\.\\/\\?\\$\\(\\)\\*\\+]+) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = "";
            getline( stream, data );
            
            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "Your client has issued a malformed or illegal request status line. That’s all we know." );
            }
            
            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "/" );
            
            return map< string, string >
            {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter + 1 ) },
                { "protocol", protocol.substr( 0, delimiter ) }
            };
        }
        
        const multimap< string, string > SessionImpl::parse_request_headers( istream& stream )
        {
            smatch matches;
            string data = "";
            multimap< string, string > headers;
            static const regex pattern( "^([^:.]*): *(.*)\\s*$" );
            
            while ( getline( stream, data ) and data not_eq "\r" )
            {
                if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 3 )
                {
                    throw runtime_error( "Your client has issued a malformed or illegal request header. That’s all we know." );
                }
                
                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }
            
            return headers;
        }
        
        void SessionImpl::parse_request( const error_code& error, const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
        
        try
        {
            if ( error )
            {
                throw runtime_error( error.message( ) );
            }
            
            istream stream( session->m_pimpl->m_request->m_pimpl->m_buffer.get( ) );
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );
            
            m_request->m_pimpl->m_path = Uri::decode( uri.get_path( ) );
            m_request->m_pimpl->m_method = items.at( "method" );
            m_request->m_pimpl->m_version = stod( items.at( "version" ) );
            m_request->m_pimpl->m_headers = parse_request_headers( stream );
            m_request->m_pimpl->m_query_parameters = uri.get_query_parameters( );
            
            callback( session );
        }
        catch ( const int status_code )
        {
            const auto error_handler = get_error_handler( );
            error_handler( status_code, runtime_error( m_settings->get_status_message( status_code ) ), session );
        }
        catch ( const regex_error& re )
        {
            const auto error_handler = get_error_handler( );
            error_handler( 500, re, session );
        }
        catch ( const runtime_error& re )
        {
            const auto error_handler = get_error_handler( );
            error_handler( 400, re, session );
        }
        catch ( const exception& ex )
        {
            const auto error_handler = get_error_handler( );
            error_handler( 500, ex, session );
        }
        catch ( ... )
        {
            auto cex = current_exception( );
            
            if ( cex not_eq nullptr )
            {
                try
                {
                    rethrow_exception( cex );
                }
                catch ( const exception& ex )
                {
                    const auto error_handler = get_error_handler( );
                    error_handler( 500, ex, session );
                }
                catch ( ... )
                {
                    const auto error_handler = get_error_handler( );
                    error_handler( 500, runtime_error( "Internal Server Error" ), session );
                }
            }
            else
            {
                const auto error_handler = get_error_handler( );
                error_handler( 500, runtime_error( "Internal Server Error" ), session );
            }
        }
    }
    
    const function< void ( const int, const exception&, const shared_ptr< Session > ) > SessionImpl::get_error_handler( void ) const
    {
        auto error_handler = ( m_resource not_eq nullptr and m_resource->m_pimpl->m_error_handler not_eq nullptr ) ? m_resource->m_pimpl->m_error_handler : m_error_handler;
        
        if ( error_handler == nullptr )
        {
            return [ ]( const int, const exception&, const shared_ptr< Session > )
            {
                return;
            };
        }
        
        return error_handler;
    }
}
