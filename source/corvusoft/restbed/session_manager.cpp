/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <ciso646>

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/session_manager.hpp"

//External Includes

//System Namespaces
using std::string;
using std::function;
using std::to_string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces

//External Namespaces

namespace restbed
{
    SessionManager::SessionManager( void )
    {
        return;
    }
    
    SessionManager::~SessionManager( void )
    {
        return;
    }
    
    void SessionManager::stop( void )
    {
        return;
    }
    
    void SessionManager::start( const shared_ptr< const Settings >& )
    {
        return;
    }
    
    void SessionManager::create( const function< void ( const shared_ptr< Session > ) >& callback )
    {
        callback( make_shared< Session >( String::empty ) );
    }
    
    void SessionManager::load( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        callback( session );
    }
    
    void SessionManager::save( const shared_ptr< Session > session, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        callback( session );
    }
}
