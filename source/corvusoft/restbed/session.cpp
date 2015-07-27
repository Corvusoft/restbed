/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/response.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;
using std::chrono::hours;
using std::chrono::minutes;
using std::chrono::seconds;
using std::chrono::milliseconds;
using std::chrono::microseconds;

//Project Namespaces
using restbed::detail::SessionImpl;

//External Namespaces

namespace restbed
{
    Session::Session( const string& id ) : m_pimpl( new SessionImpl )
    {
        m_pimpl->set_id( id );
    }
    
    Session::~Session( void )
    {
        return;
    }

    bool Session::has( const string& name ) const
    {
        return m_pimpl->has( name );
    }

    void Session::erase( const string& name )
    {
        return m_pimpl->erase( name );
    }

    const set< string > Session::keys( void ) const
    {
        return m_pimpl->keys( );
    }
    
    bool Session::is_open( void ) const
    {
        return m_pimpl->is_open( );
    }
    
    bool Session::is_closed( void ) const
    {
        return m_pimpl->is_closed( );
    }
    
    void Session::close( const Bytes& body )
    {
        m_pimpl->close( body );
    }
    
    void Session::close( const Response& response )
    {
        m_pimpl->close( response );
    }

    void Session::close( const string& body )
    {
        m_pimpl->close( body );
    }
    
    void Session::close( const int status, const Bytes& body )
    {
        static multimap< string, string > empty;
        m_pimpl->close( status, body, empty );
    }
    
    void Session::close( const int status, const string& body )
    {
        static multimap< string, string > empty;
        m_pimpl->close( status, body, empty );
    }
    
    void Session::close( const int status, const multimap< string, string >& headers )
    {
        m_pimpl->close( status, "", headers );
    }
    
    void Session::close( const int status, const string& body, const multimap< string, string >& headers )
    {
        m_pimpl->close( status, body, headers );
    }
    
    void Session::close( const int status, const Bytes& body, const multimap< string, string >& headers )
    {
        m_pimpl->close( status, body, headers );
    }
    
    void Session::yield( const Bytes& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( body, callback );
    }

    void Session::yield( const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( body, callback );
    }
    
    void Session::yield( const Response& response, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( response, callback );
    }

    void Session::yield( const int status, const Bytes& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        static multimap< string, string > empty;
        m_pimpl->yield( status, body, empty, callback );
    }

    void Session::yield( const int status, const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        static multimap< string, string > empty;
        m_pimpl->yield( status, body, empty, callback );
    }
    
    void Session::yield( const int status, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( status, "", headers, callback );
    }
    
    void Session::yield( const int status, const string& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( status, body, headers, callback );
    }
    
    void Session::yield( const int status, const Bytes& body, const multimap< string, string >& headers, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( status, body, headers, callback );
    }
    
    void Session::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->fetch( callback );
    }
    
    void Session::fetch( const size_t length, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
    {
        m_pimpl->fetch( length, callback );
    }
    
    void Session::fetch( const string& delimiter, const function< void ( const shared_ptr< Session >&, const Bytes& ) >& callback )
    {
        m_pimpl->fetch( delimiter, callback );
    }
    
    void Session::wait_for( const hours& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( delay, callback );
    }
    
    void Session::wait_for( const minutes& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( delay, callback );
    }
    
    void Session::wait_for( const seconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( delay, callback );
    }
    
    void Session::wait_for( const milliseconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( delay, callback );
    }
    
    void Session::wait_for( const microseconds& delay, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( delay, callback );
    }

    void Session::wait_for( const hours& interval, const function< hours ( const hours& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( interval, trigger, callback );
    }
    
    void Session::wait_for( const minutes& interval, const function< minutes ( const minutes& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( interval, trigger, callback );
    }
    
    void Session::wait_for( const seconds& interval, const function< seconds ( const seconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( interval, trigger, callback );
    }
    
    void Session::wait_for( const milliseconds& interval, const function< milliseconds ( const milliseconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( interval, trigger, callback );
    }
    
    void Session::wait_for( const microseconds& interval, const function< microseconds ( const microseconds& ) >& trigger, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->wait_for( interval, trigger, callback );
    }
    
    const string& Session::get_id( void ) const
    {
        return m_pimpl->get_id( );
    }
    
    const string Session::get_origin( void ) const
    {
        return m_pimpl->get_origin( );
    }
    
    const string Session::get_destination( void ) const
    {
        return m_pimpl->get_destination( );
    }
    
    const shared_ptr< const Request > Session::get_request(  void ) const
    {
        return m_pimpl->get_request( );
    }
    
    const shared_ptr< const Resource > Session::get_resource(  void ) const
    {
        return m_pimpl->get_resource( );
    }
    
    const multimap< string, string >& Session::get_headers( void ) const
    {
        return m_pimpl->get_headers( );
    }

    const ContextValue& Session::get( const string& name ) const
    {
        return m_pimpl->get( name );
    }

    const ContextValue& Session::get( const string& name, const ContextValue& default_value ) const
    {
        return m_pimpl->get( name, default_value );
    }

    void Session::set( const string& name, const ContextValue& value )
    {
        m_pimpl->set( name, value );
    }
    
    void Session::set_header( const string& name, const string& value )
    {
        m_pimpl->set_header( name, value );
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_headers( values );
    }
}
