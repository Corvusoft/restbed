/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/session_impl.h"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;

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

    void Session::close( void )
    {
        m_pimpl->close( );
    }

    void Session::close( const int status, const string& status_message )
    {
        m_pimpl->close( status, status_message );
    }

    void Session::fetch( const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->fetch( shared_ptr< Session >( this ), callback );
    }

    const string& Session::get_id( void ) const
    {
        return m_pimpl->get_id( );
    }

    const shared_ptr< const Request > Session::get_request(  void ) const
    {
        return m_pimpl->get_request( );
    }

    const shared_ptr< const Resource > Session::get_resource(  void ) const
    {
        return m_pimpl->get_resource( );
    }

    void Session::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_default_headers( values );
    }
}
