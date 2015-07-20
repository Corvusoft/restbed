/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <stdexcept>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes
#include <corvusoft/restbed/string.hpp>

//System Namespaces
using std::set;
using std::pair;
using std::string;
using std::vector;
using std::function;
using std::multimap;
using std::exception;
using std::shared_ptr;
using std::stable_sort;
using std::invalid_argument;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_paths( ),
            m_rules( ),
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

        void ResourceImpl::add_rule( const shared_ptr< Rule >& rule )
        {
            m_rules.push_back( rule );

            stable_sort( m_rules.begin( ), m_rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
            {
                return *lhs < *rhs;
            } );
        }

        void ResourceImpl::add_rule( const shared_ptr< Rule >& rule, const int priority )
        {
            rule->set_priority( priority );
            m_rules.push_back( rule );

            stable_sort( m_rules.begin( ), m_rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
            {
                return *lhs < *rhs;
            } );
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
        
        const set< string > ResourceImpl::get_methods( void ) const
        {
            set< string > methods;

            for ( auto entry : m_method_handlers )
            {
                methods.insert( entry.first );
            }

            return methods;
        }

        const vector< shared_ptr< Rule > >& ResourceImpl::get_rules( void ) const
        {
            return m_rules;
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
            
            return decltype( m_method_handlers )( m_method_handlers.lower_bound( method ), m_method_handlers.upper_bound( method ) );
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
            
            m_method_handlers.insert( make_pair( method, make_pair( filters, callback ) ) );
        }
    }
}
