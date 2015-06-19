/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/session_manager_impl.h"

//External Includes
#include <corvusoft/framework/unique_id>

//System Namespaces
using std::function;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces

//External Namespaces
using framework::UniqueId;

namespace restbed
{
    namespace detail
    {
        SessionManagerImpl::SessionManagerImpl( void )
        {
            return;
        }

        SessionManagerImpl::~SessionManagerImpl( void )
        {
            return;
        }

        void SessionManagerImpl::stop( void )
        {
            return;
        }

        void SessionManagerImpl::start( const shared_ptr< const Settings >& )
        {
            return;
        }

        void SessionManagerImpl::create( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            auto session = make_shared< Session >( UniqueId::generate( ).to_string( ) );
            callback( session );
        }

        void SessionManagerImpl::purge( shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            session.reset( );
            callback( nullptr );
        }

        void SessionManagerImpl::load( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( session->is_closed( ) )
            {
                return;
            }

            callback( session );
        }
    }
}
