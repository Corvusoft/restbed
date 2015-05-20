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
using std::map;
using std::string;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces

//External Namespaces
using framework::UniqueId;

namespace restbed
{
    namespace detail
    {
        SessionManagerImpl::SessionManagerImpl( const Settings& settings ) : SessionManager( settings ),
            m_sessions( )
        {
            return;
        }
        
        SessionManagerImpl::~SessionManagerImpl( void )
        {
            return;
        }

        shared_ptr< Session > SessionManagerImpl::create( void )
        {
            auto session = make_shared< Session >( UniqueId::generate( ).to_string( ) );
            m_sessions[ session->get_id( ) ] = session;

            return session;
        }

        void SessionManagerImpl::load( shared_ptr< Session >& session )
        {
            //perform async operation ex. Http::async( );
            //restbed::wait_for( seconds( 10 ), bind( session, callback ) );
            return;
        }
    }
}
