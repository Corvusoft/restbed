/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/detail/resource_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::set;
using std::pair;
using std::string;
using std::function;
using std::multimap;
using std::exception;
using std::shared_ptr;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using framework::String;

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_paths( ),
            m_methods( ),
            m_default_headers( ),
            m_failed_filter_validation_handler( nullptr ),
            m_error_handler( nullptr ),
            m_authentication_handler( nullptr ),
            m_method_handlers( )
        {
            return;
        }

        ResourceImpl::~ResourceImpl( void )
        {
            return;
        }

        void ResourceImpl::authenticate( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( m_authentication_handler not_eq nullptr )
            {
                m_authentication_handler( session, callback );
            }
            else
            {
                callback( session );
            }
        }

        const set< string >& ResourceImpl::get_paths( void ) const
        {
            return m_paths;
        }

        const set< string >& ResourceImpl::get_methods( void ) const
        {
            return m_methods;
        }

        const multimap< string, string >& ResourceImpl::get_default_headers( void ) const
        {
            return m_default_headers;
        }

        const function< void ( const shared_ptr< Session >& ) >& ResourceImpl::get_failed_filter_validation_handler( void ) const
        {
            return m_failed_filter_validation_handler;
        }

        const function< void ( const int, const exception&, const shared_ptr< Session >& ) > ResourceImpl::get_error_handler( void ) const
        {
            return m_error_handler;
        }

        multimap< string, pair< multimap< string, string >, function< void ( const shared_ptr< Session >& ) > > > ResourceImpl::get_method_handlers( const string& method ) const
        {
            if ( method.empty( ) )
            {
                return m_method_handlers;
            }

            return decltype( m_method_handlers )( m_method_handlers.lower_bound( method ),
                                                  m_method_handlers.upper_bound( method ) );
        }

        void ResourceImpl::set_paths( const set< string >& values )
        {
            m_paths = values;
        }

        void ResourceImpl::set_default_header( const string& name, const string& value )
        {
            m_default_headers.insert( make_pair( name, value ) );
        }

        void ResourceImpl::set_default_headers( const multimap< string, string >& values )
        {
            m_default_headers = values;
        }

        void ResourceImpl::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session >& ) >& value )
        {
            m_failed_filter_validation_handler = value;
        }

        void ResourceImpl::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session >& ) >& value )
        {
            m_error_handler = value;
        }

        void ResourceImpl::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
        {
            m_authentication_handler = value;
        }
        
        void ResourceImpl::set_method_handler( const string& method, const multimap< string, string >& filters, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( method.empty( ) )
            {
                throw invalid_argument( "Attempt to set resource handler to an empty protocol method." );
            }

            m_methods.insert( method );
            m_method_handlers.insert( make_pair( method, make_pair( filters, callback ) ) );
        }
    }
}
