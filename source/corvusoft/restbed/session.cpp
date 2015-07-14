/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/detail/session_impl.hpp"

//External Includes

//System Namespaces
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
    
    bool Session::is_open( void ) const
    {
        return m_pimpl->is_open( );
    }
    
    bool Session::is_closed( void ) const
    {
        return m_pimpl->is_closed( );
    }
    
    void Session::purge( const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->purge( callback );
    }
    
    void Session::close( const Bytes& body )
    {
        m_pimpl->close( body );
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
    
    void Session::yield( const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( body, callback );
    }
    
    void Session::yield( const Bytes& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->yield( body, callback );
    }
    
    void Session::yield( const int status, const string& body, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        static multimap< string, string > empty;
        m_pimpl->yield( status, body, empty, callback );
    }
    
    void Session::yield( const int status, const Bytes& body, const function< void ( const shared_ptr< Session >& ) >& callback )
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
    
    void Session::set_header( const string& name, const string& value )
    {
        m_pimpl->set_header( name, value );
    }
    
    void Session::set_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_headers( values );
    }
}
