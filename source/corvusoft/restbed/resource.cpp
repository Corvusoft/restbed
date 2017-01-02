/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

//System Includes
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <stdexcept>
#include <functional>
#include <algorithm>

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/session.hpp"
#include "corvusoft/restbed/resource.hpp"
#include "corvusoft/restbed/detail/resource_impl.hpp"

//External Includes

//System Namespaces
using std::set;
using std::string;
using std::multimap;
using std::function;
using std::exception;
using std::unique_ptr;
using std::shared_ptr;
using std::invalid_argument;

//Project Namespaces
using restbed::detail::ResourceImpl;

//External Namespaces

namespace restbed
{
    Resource::Resource( void ) : m_pimpl( new ResourceImpl )
    {
        return;
    }
    
    Resource::~Resource( void )
    {
        return;
    }
    
    void Resource::add_rule( const shared_ptr< Rule >& rule )
    {
        if ( rule not_eq nullptr )
        {
            m_pimpl->m_rules.push_back( rule );
            
            stable_sort( m_pimpl->m_rules.begin( ), m_pimpl->m_rules.end( ), [ ]( const shared_ptr< const Rule >& lhs, const shared_ptr< const Rule >& rhs )
            {
                return lhs->get_priority( ) < rhs->get_priority( );
            } );
        }
    }
    
    void Resource::add_rule( const shared_ptr< Rule >& rule, const int priority )
    {
        if ( rule not_eq nullptr )
        {
            rule->set_priority( priority );
            add_rule( rule );
        }
    }
    
    void Resource::set_path( const string& value )
    {
        m_pimpl->m_paths = { value };
    }
    
    void Resource::set_paths( const set< string >& values )
    {
        m_pimpl->m_paths = values;
    }
    
    void Resource::set_default_header( const string& name, const string& value )
    {
        m_pimpl->m_default_headers.insert( make_pair( name, value ) );
    }
    
    void Resource::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->m_default_headers = values;
    }
    
    void Resource::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session > ) >& value )
    {
        m_pimpl->m_failed_filter_validation_handler = value;
    }
    
    void Resource::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session > ) >& value )
    {
        m_pimpl->m_error_handler = value;
    }
    
    void Resource::set_authentication_handler( const function< void ( const shared_ptr< Session >, const function< void ( const shared_ptr< Session > ) >& ) >& value )
    {
        m_pimpl->m_authentication_handler = value;
    }
    
    void Resource::set_method_handler( const string& method, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        static const multimap< string, string > empty { };
        set_method_handler( method, empty, callback );
    }
    
    void Resource::set_method_handler( const string& method, const multimap< string, string >& filters, const function< void ( const shared_ptr< Session > ) >& callback )
    {
        if ( method.empty( ) )
        {
            throw invalid_argument( "Attempt to set resource handler to an empty protocol method." );
        }
        
        if ( callback not_eq nullptr )
        {
            m_pimpl->m_methods.insert( method );
            m_pimpl->m_method_handlers.insert( make_pair( method, make_pair( filters, callback ) ) );
        }
    }
}
