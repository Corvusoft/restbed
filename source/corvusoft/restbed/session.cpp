/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/context_value.hpp"
#include "corvusoft/restbed/session_manager.hpp"
#include "corvusoft/restbed/detail/socket_impl.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp" 

//External Includes
#include <asio.hpp>

//System Namespaces
using std::set;
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;
using std::runtime_error;
using std::invalid_argument;
using std::chrono::milliseconds;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces
using asio::buffer;
using asio::error_code;

namespace restbed
{
    Session::Session( const string& id ) : m_pimpl( new SessionImpl )
    {
        m_pimpl->m_id = id;
    }
    
    Session::~Session( void )
    {
        delete m_pimpl;
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
        std::set< std::string > keys;
        
        for ( const auto& value : m_pimpl->m_context )
        {
            keys.insert( keys.end( ), value.first );
        }
        
        return keys;
    }
    
    bool Session::is_open( void ) const
    {
        return m_pimpl->m_socket not_eq nullptr and m_pimpl->m_socket->is_open( );
    }
    
    bool Session::is_closed( void ) const
    {
        return not is_open( );
    }
    
    void Session::close( const Bytes& body )
    {
        auto session = shared_from_this( );
        
        m_pimpl->m_socket->write( body, [ this, session ]( const asio::error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            else
            {
                m_pimpl->m_manager->save( session, [ this, session ]( const shared_ptr< Session > )
                {
                    m_pimpl->m_socket->close( );
                } );
            }
        } );
    }
    
    void Session::close( const Response& response )
    {
        auto session = shared_from_this( );
        
        m_pimpl->transmit( response, [ this, session ]( const asio::error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Close failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            
            m_pimpl->m_manager->save( session, [ this ]( const shared_ptr< Session > )
            {
                m_pimpl->m_socket->close( );
            } );
        } );
    }
    
    void Session::close( const string& body )
    {
        close( String::to_bytes( body ) );
    }
    
    void Session::close( const int status, const Bytes& body )
    {
        static multimap< string, string > empty;
        close( status, body, empty );
    }
    
    void Session::close( const int status, const string& body )
    {
        static multimap< string, string > empty;
        close( status, body, empty );
    }
    
    void Session::close( const int status, const multimap< string, string >& headers )
    {
        close( status, "", headers );
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
        
        m_pimpl->m_socket->write( body, [ this, session, callback ]( const asio::error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            else
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
        
        m_pimpl->transmit( response, [ this, session, callback ]( const asio::error_code & error, size_t )
        {
            if ( error )
            {
                const auto message = String::format( "Yield failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            else
            {
                if ( callback == nullptr )
                {
                    m_pimpl->fetch( session, m_pimpl->m_router );
                }
                else
                {
                    callback( session );
                }
            }
        } );
    }
    
    void Session::yield( const int status, const Bytes& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        static multimap< string, string > empty;
        yield( status, body, empty, callback );
    }
    
    void Session::yield( const int status, const string& body, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        static multimap< string, string > empty;
        yield( status, body, empty, callback );
    }
    
    void Session::yield( const int status, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        yield( status, "", headers, callback );
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
    
    void Session::fetch( const function< void ( const shared_ptr< Session > ) >& callback )
    {
        m_pimpl->fetch( shared_from_this( ), callback );
    }
    
    void Session::fetch( const size_t length, const function< void ( const shared_ptr< Session >, const Bytes& ) >& callback )
    {
        auto session = shared_from_this( );
        
        if ( length > m_pimpl->m_request->m_pimpl->m_buffer->size( ) )
        {
            size_t size = length - m_pimpl->m_request->m_pimpl->m_buffer->size( );
            
            m_pimpl->m_socket->read( m_pimpl->m_request->m_pimpl->m_buffer, size, [ this, session, length, callback ]( const asio::error_code & error, size_t )
            {
                if ( error )
                {
                    const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                    m_pimpl->failure( session, 500, runtime_error( message ) );
                }
                else
                {
                    m_pimpl->fetch_body( length, session, callback );
                }
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
        
        m_pimpl->m_socket->read( m_pimpl->m_request->m_pimpl->m_buffer, delimiter, [ this, session, callback ]( const asio::error_code & error, size_t length )
        {
            if ( error )
            {
                const auto message = String::format( "Fetch failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            else
            {
                m_pimpl->fetch_body( length, session, callback );
            }
        } );
    }
    
    void Session::sleep_for( const milliseconds& delay, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        auto session = shared_from_this( );
        
        m_pimpl->m_socket->sleep_for( delay, [ delay, session, callback, this ]( const error_code & error )
        {
            if ( error )
            {
                const auto message = String::format( "Wait failed: %s", error.message( ).data( ) );
                m_pimpl->failure( session, 500, runtime_error( message ) );
            }
            else
            {
                if ( callback not_eq nullptr )
                {
                    callback( session );
                }
            }
        } );
    }
    
    const string& Session::get_id( void ) const
    {
        return m_pimpl->m_id;
    }
    
    const string Session::get_origin( void ) const
    {
        if ( m_pimpl->m_socket == nullptr )
        {
            return "";
        }
        
        return m_pimpl->m_socket->get_remote_endpoint( );
    }
    
    const string Session::get_destination( void ) const
    {
        if ( m_pimpl->m_socket == nullptr )
        {
            return "";
        }
        
        return m_pimpl->m_socket->get_local_endpoint( );
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
    
    void Session::set_header( const string& name, const string& value )
    {
        m_pimpl->m_headers.insert( make_pair( name, value ) );
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_headers = values;
    }
}
