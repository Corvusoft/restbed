/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <utility>
#include <ciso646>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/uri.hpp"
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
using asio::error_code;

namespace restbed
{
    namespace detail
    {
        SessionImpl::SessionImpl( void ) : id( "" ),
            logger( nullptr ),
            socket( nullptr ),
            request( nullptr ),
            resource( nullptr ),
            settings( nullptr ),
            buffer( nullptr ),
            manager( nullptr ),
            headers( ),
            context( ),
            router( nullptr ),
            error_handler( nullptr )
        {
            return;
        }
        
        SessionImpl::~SessionImpl( void )
        {
            return;
        }

        void SessionImpl::fetch( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
        {            
            buffer = make_shared< asio::streambuf >( );
            
            socket->read( buffer, "\r\n\r\n", bind( &SessionImpl::parse_request, this, _1, session, callback ) );
        }
        
        void SessionImpl::fetch_body( const size_t length, const shared_ptr< Session > session, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback ) const
        {
            const auto data_ptr = asio::buffer_cast< const Byte* >( buffer->data( ) );
            const auto data = Bytes( data_ptr, data_ptr + length );
            buffer->consume( length );

            auto& body = request->m_pimpl->body;

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
        
        void SessionImpl::log( const Logger::Level level, const string& message ) const
        {
            if ( logger not_eq nullptr )
            {
                logger->log( level, "%s", message.data( ) );
            }
        }
        
        void SessionImpl::failure( const shared_ptr< Session > session, const int status, const exception& error ) const
        {
            const auto handler = ( resource not_eq nullptr and resource->m_pimpl->error_handler not_eq nullptr ) ? resource->m_pimpl->error_handler : this->error_handler;
            
            if ( handler not_eq nullptr )
            {
                handler( status, error, session );
            }
            else
            {
                log( Logger::Level::ERROR, String::format( "Error %i, %s", status, error.what( ) ) );
                
                string body = error.what( );
                session->close( status, body, { { "Content-Type", "text/plain" }, { "Content-Length", ::to_string( body.length( ) ) } } );
            }
        }
        
        void SessionImpl::transmit( const Response& response, const function< void ( const asio::error_code&, size_t ) >& callback ) const
        {
            auto hdrs = settings->get_default_headers( );
            
            if ( resource not_eq nullptr )
            {
                const auto resource_headers = resource->m_pimpl->default_headers;
                hdrs.insert( resource_headers.begin( ), resource_headers.end( ) );
            }
            
            hdrs.insert( headers.begin( ), headers.end( ) );
            
            auto response_headers = response.get_headers( );
            hdrs.insert( response_headers.begin( ), response_headers.end( ) );
            
            Response payload;
            payload.set_headers( hdrs );
            payload.set_body( response.get_body( ) );
            payload.set_version( response.get_version( ) );
            payload.set_protocol( response.get_protocol( ) );
            payload.set_status_code( response.get_status_code( ) );
            payload.set_status_message( response.get_status_message( ) );
            
            if ( payload.get_status_message( ).empty( ) )
            {
                payload.set_status_message( settings->get_status_message( payload.get_status_code( ) ) );
            }
            
            socket->write( payload.to_bytes( ), callback );
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
        
        void SessionImpl::parse_request( const asio::error_code& error, const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
        
        try
        {
            if ( error )
            {
                throw runtime_error( error.message( ) );
            }
            
            istream stream( buffer.get( ) );
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );
            
            request = make_shared< Request >( );
            request->m_pimpl->path = Uri::decode( uri.get_path( ) );
            request->m_pimpl->method = items.at( "method" );
            request->m_pimpl->version = stod( items.at( "version" ) );
            request->m_pimpl->headers = parse_request_headers( stream );
            request->m_pimpl->query_parameters = uri.get_query_parameters( );

            callback( session );
        }
        catch ( const int status_code )
        {
            runtime_error re( settings->get_status_message( status_code ) );
            failure( session, status_code, re );
        }
        catch ( const regex_error& re )
        {
            failure( session, 500, re );
        }
        catch ( const runtime_error& re )
        {
            failure( session, 400, re );
        }
        catch ( const exception& ex )
        {
            failure( session, 500, ex );
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
                    failure( session, 500, ex );
                }
                catch ( ... )
                {
                    runtime_error re( "Internal Server Error" );
                    failure( session, 500, re );
                }
            }
            else
            {
                runtime_error re( "Internal Server Error" );
                failure( session, 500, re );
            }
        }
    }
}
