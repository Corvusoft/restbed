/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

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
using std::shared_ptr;

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

    void Resource::add_rule( const shared_ptr< const Rule >& rule )
    {
        m_pimpl->add_rule( rule );
    }
    
    void Resource::set_path( const string& value )
    {
        m_pimpl->set_paths( { value } );
    }
    
    void Resource::set_paths( const set< string >& values )
    {
        m_pimpl->set_paths( values );
    }
    
    void Resource::set_default_header( const string& name, const string& value )
    {
        m_pimpl->set_default_header( name, value );
    }
    
    void Resource::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_default_headers( values );
    }
    
    void Resource::set_failed_filter_validation_handler( const function< void ( const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_failed_filter_validation_handler( value );
    }
    
    void Resource::set_error_handler( const function< void ( const int, const exception&, const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_error_handler( value );
    }
    
    void Resource::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
    {
        m_pimpl->set_authentication_handler( value );
    }
    
    void Resource::set_method_handler( const string& method, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        static const multimap< string, string > empty;
        m_pimpl->set_method_handler( method, empty, callback );
    }
    
    void Resource::set_method_handler( const string& method, const multimap< string, string >& filters, const function< void ( const shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->set_method_handler( method, filters, callback );
    }
}
