/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <chrono>
#include <random>

//Project Includes
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/settings.hpp"
#include "corvusoft/restbed/detail/session_manager_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::mt19937;
using std::function;
using std::shared_ptr;
using std::make_shared;
using std::chrono::system_clock;
using std::uniform_int_distribution;

//Project Namespaces

//External Namespaces

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
            static const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            static uniform_int_distribution< > selector( 0, charset.size( ) - 1 );
            static mt19937 generator( system_clock::now( ).time_since_epoch( ).count( ) );

            string key = "";
            for ( int index = 0; index < 32; index++ )
            {
                key += ( charset.at( selector( generator ) ) );
            }

            auto session = make_shared< Session >( key );
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
