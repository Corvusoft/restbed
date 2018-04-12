/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>
#include <system_error>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/web_socket.hpp"
#include "corvusoft/restbed/context_value.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_impl.hpp"
#include "corvusoft/restbed/detail/web_socket_manager_impl.hpp"

//External Includes
#include <asio/buffer.hpp>

//System Namespaces
using std::set;
using std::string;
using std::function;
using std::multimap;
using std::error_code;
using std::unique_ptr;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;
using std::placeholders::_1;
using std::placeholders::_2;
using std::invalid_argument;
using std::chrono::milliseconds;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;

namespace restbed
{
    static Bytes empty_body = { };
    static multimap< string, string > empty_headers = { };
    
    Session::Session( const string& id ) : m_pimpl( new SessionImpl )
    {
        m_pimpl->m_id = id;
    }
    
    Session::~Session( void )
    {
        return;
    }
    
    bool Session::has( const string& name ) const
    {
        return m_pimpl->m_context.find( name ) not_eq m_pimpl->m_context.end( );
    }
    
    void Session::erase( const string& name )
    {
        if ( name.empty( ) )
        {
            m_pimpl->m_context.clear( );
        }
        else
        {
            m_pimpl->m_context.erase( name );
        }
    }
    
    const set< string > Session::keys( void ) const
    {
        std::set< string > keys;
        
        for ( const auto& value : m_pimpl->m_context )
        {
            keys.insert( value.first );
        }
        
        return keys;
    }
    
    bool Session::is_open( void ) const
    {
        return m_pimpl->m_request not_eq nullptr and
               m_pimpl->m_request->m_pimpl->m_socket not_eq nullptr and
               m_pimpl->m_request->m_pimpl->m_socket->is_open( );
    }
    
    bool Session::is_closed( void ) const
    {
        return not is_open( );
    }
    
    void Session::close( const Bytes& body )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Close failed: session already closed." ), session );
        }
        
        m_pimpl->m_request->m_pimpl->m_socket->start_write( body, [ this, session ]( const error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            m_pimpl->m_manager->save( session, [ this, session ]( const shared_ptr< Session > )
            {
                m_pimpl->m_request->m_pimpl->m_socket->close( );
            } );
        } );
    }
    
    void Session::close( const Response& response )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Close failed: session already closed." ), session );
        }
        
        m_pimpl->transmit( response, [ this, session ]( const error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            m_pimpl->m_manager->save( session, [ this ]( const shared_ptr< Session > )
            {
                m_pimpl->m_request->m_pimpl->m_socket->close( );
            } );
        } );
    }
    
    void Session::close( const string& body )
    {
        close( String::to_bytes( body ) );
    }
    
    void Session::close( const int status, const Bytes& body )
    {
        close( status, body, empty_headers );
    }
    
    void Session::close( const int status, const string& body )
    {
        close( status, String::to_bytes( body ), empty_headers );
    }
    
    void Session::close( const int status, const multimap< string, string >& headers )
    {
        close( status, empty_body, headers );
    }
    
    void Session::close( const int status, const string& body, const multimap< string, string >& headers )
    {
        close( status, String::to_bytes( body ), headers );
    }
    
    void Session::close( const int status, const Bytes& body, const multimap< string, string >& headers )
    {
        Response response;
        response.set_body( body );
        response.set_headers( headers );
        response.set_status_code( status );
        
        close( response );
    }
    
    void Session::yield( const Bytes& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Yield failed: session already closed." ), session );
        }
        
        m_pimpl->m_request->m_pimpl->m_socket->start_write( body, [ this, session, callback ]( const error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            if ( callback not_eq nullptr )
            {
                callback( session );
            }
        } );
    }
    
    void Session::yield( const string& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( String::to_bytes( body ), callback );
    }
    
    void Session::yield( const Response& response, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Yield failed: session already closed." ), session );
        }
        
        m_pimpl->transmit( response, [ this, session, callback ]( const error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            if ( callback == nullptr )
            {
                m_pimpl->m_request->m_pimpl->m_socket->start_read( m_pimpl->m_request->m_pimpl->m_buffer, "\r\n\r\n", [ this, session ]( const error_code & error, const size_t length )
                {
                    m_pimpl->m_keep_alive_callback( error, length, session );
                } );
                
                return;
            }
            else
            {
                callback( session );
            }
        } );
    }
    
    void Session::yield( const int status, const Bytes& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( status, body, empty_headers, callback );
    }
    
    void Session::yield( const int status, const string& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( status, String::to_bytes( body ), empty_headers, callback );
    }
    
    void Session::yield( const int status, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( status, empty_body, headers, callback );
    }
    
    void Session::yield( const int status, const string& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( status, String::to_bytes( body ), headers, callback );
    }
    
    void Session::yield( const int status, const Bytes& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        Response response;
        response.set_body( body );
        response.set_headers( headers );
        response.set_status_code( status );
        
        yield( response, callback );
    }
    
    void Session::fetch( const size_t length, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Fetch failed: session already closed." ), session );
        }
        
        if ( length > m_pimpl->m_request->m_pimpl->m_buffer->size( ) )
        {
            size_t size = length - m_pimpl->m_request->m_pimpl->m_buffer->size( );
            
            m_pimpl->m_request->m_pimpl->m_socket->start_read( m_pimpl->m_request->m_pimpl->m_buffer, size, [ this, session, length, callback ]( const error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                    const auto error_handler = m_pimpl->get_error_handler( );
                    return error_handler( 500, runtime_error( message ), session );
                }
                
                m_pimpl->fetch_body( length, session, callback );
            } );
        }
        else
        {
            m_pimpl->fetch_body( length, session, callback );
        }
    }
    
    void Session::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Fetch failed: session already closed." ), session );
        }
        
        m_pimpl->m_request->m_pimpl->m_socket->start_read( m_pimpl->m_request->m_pimpl->m_buffer, delimiter, [ this, session, callback ]( const error_code & error, size_t length )
        {
            if ( error )
            {
                const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            m_pimpl->fetch_body( length, session, callback );
        } );
    }
    
    
    void Session::upgrade( const int status, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        upgrade( status, empty_body, empty_headers, callback );
    }
    
    void Session::upgrade( const int status, const Bytes& body, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        upgrade( status, body, empty_headers, callback );
    }
    
    void Session::upgrade( const int status, const string& body, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        upgrade( status, String::to_bytes( body ), empty_headers, callback );
    }
    
    void Session::upgrade( const int status, const multimap< string, string >& headers, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        upgrade( status, empty_body, headers, callback );
    }
    
    void Session::upgrade( const int status, const Bytes& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        auto socket = m_pimpl->m_web_socket_manager->create( shared_from_this( ) );
        yield( status, body, headers, bind( callback, socket ) );
    }
    
    void Session::upgrade( const int status, const string& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< WebSocket > ) >& callback )
    {
        upgrade( status, String::to_bytes( body ), headers, callback );
    }
    
    void Session::sleep_for( const milliseconds& delay, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( is_closed( ) )
        {
            const auto error_handler = m_pimpl->get_error_handler( );
            return error_handler( 500, runtime_error( "Sleep failed: session already closed." ), session );
        }
        
        m_pimpl->m_request->m_pimpl->m_socket->sleep_for( delay, [ delay, session, callback, this ]( const error_code & error )
        {
            if ( error )
            {
                const auto message = String::format( "Wait failed: %s", error.message( ).data( ) );
                const auto error_handler = m_pimpl->get_error_handler( );
                return error_handler( 500, runtime_error( message ), session );
            }
            
            if ( callback not_eq nullptr )
            {
                callback( session );
            }
        } );
    }
    
    const string& Session::get_id( void ) const
    {
        return m_pimpl->m_id;
    }
    
    const string Session::get_origin( void ) const
    {
        if ( m_pimpl->m_request == nullptr or m_pimpl->m_request->m_pimpl->m_socket == nullptr )
        {
            return "";
        }
        
        return m_pimpl->m_request->m_pimpl->m_socket->get_remote_endpoint( );
    }
    
    const string Session::get_destination( void ) const
    {
        if ( m_pimpl->m_request == nullptr or m_pimpl->m_request->m_pimpl->m_socket == nullptr )
        {
            return "";
        }
        
        return m_pimpl->m_request->m_pimpl->m_socket->get_local_endpoint( );
    }
    
    const shared_ptr< const Request > Session::get_request(  void ) const
    {
        return m_pimpl->m_request;
    }
    
    const shared_ptr< const Resource > Session::get_resource(  void ) const
    {
        return m_pimpl->m_resource;
    }
    
    const multimap< string, string >& Session::get_headers( void ) const
    {
        return m_pimpl->m_headers;
    }
    
    const ContextValue& Session::get( const string& name ) const
    {
        return m_pimpl->m_context.at( name );
    }
    
    const ContextValue& Session::get( const string& name, const ContextValue& default_value ) const
    {
        if ( has( name ) )
        {
            return m_pimpl->m_context.at( name );
        }
        
        return default_value;
    }
    
    void Session::set_id( const string& value )
    {
        m_pimpl->m_id = value;
    }
    
    void Session::set( const string& name, const ContextValue& value )
    {
        if ( has( name ) )
        {
            m_pimpl->m_context.erase( name );
        }
        
        m_pimpl->m_context.insert( make_pair( name, value ) );
    }
    
    void Session::add_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Session::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.erase( name );
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
}
