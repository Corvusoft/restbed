/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <chrono>
#include <random>
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/detail/session_manager_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::mt19937;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::uniform_int_distribution;
using std::chrono::high_resolution_clock;

//Project Namespaces
using restbed::detail::SessionManagerImpl;

//External Namespaces

namespace restbed
{
    SessionManager::SessionManager( void ) : m_pimpl( new SessionManagerImpl )
    {
        return;
    }
    
    SessionManager::~SessionManager( void )
    {
        delete m_pimpl;
    }
    
    void SessionManager::stop( void )
    {
        return;
    }
    
    void SessionManager::start( const shared_ptr< const Settings >& )
    {
        return;
    }
    
    void SessionManager::create( const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        if ( callback == nullptr )
        {
            return;
        }
        
        static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static uniform_int_distribution< > selector( 0, charset.size( ) - 1 );
        static mt19937 generator( high_resolution_clock::now( ).time_since_epoch( ).count( ) );
        
        string key = "";
        
        for ( int index = 0; index < 32; index++ )
        {
            key += ( charset.at( selector( generator ) ) );
        }
        
        m_pimpl->sessions[ key ] = make_shared< Session >( key );
        callback( m_pimpl->sessions.at( key ) );
    }
    
    void SessionManager::purge( shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        if ( session not_eq nullptr )
        {
            m_pimpl->sessions.erase( session->get_id( ) );
            session.reset( );
        }
        
        if ( callback not_eq nullptr )
        {
            callback( nullptr );
        }
    }
    
    void SessionManager::load( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        if ( session == nullptr or session->is_closed( ) or callback == nullptr )
        {
            return;
        }
        
        callback( session );
    }
}
