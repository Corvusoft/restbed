/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/detail/resource_impl.h"

//External Includes

//System Namespaces
using std::set;
using std::pair;
using std::string;
using std::multimap;
using std::function;

//Project Namespaces
using restbed::detail::ResourceImpl;

//External Namespaces

namespace restbed
{
    Resource::Resource( void ) : m_pimpl( new ResourceImpl )
    {
        return;
    }
    
    Resource::Resource( const Resource& original ) : m_pimpl( new ResourceImpl( *original.m_pimpl ) )
    {
        return;
    }
    
    Resource::~Resource( void )
    {
        return;
    }

    string Resource::get_id( void ) const
    {
        return m_pimpl->get_id( );
    }

    set< string > Resource::get_paths( void ) const
    {
        return m_pimpl->get_paths( );
    }
    
    multimap< string, pair< multimap< string, string >, function< Response ( const Request& ) > > >
    Resource::get_method_handlers( const string& method ) const
    {
        return m_pimpl->get_method_handlers( method );
    }

    void Resource::set_paths( const set< string >& values )
    {
        m_pimpl->set_paths( values );
    }

    void Resource::set_method_handler( const string& method,
                                       const function< Response ( const Request& ) >& callback )
    {
        static const multimap< string, string > empty;
        m_pimpl->set_method_handler( method, empty, callback );
    }
    
    void Resource::set_method_handler( const string& method,
                                       const multimap< string, string >& filters,
                                       const function< Response ( const Request& ) >& callback )
    {
        m_pimpl->set_method_handler( method, filters, callback );
    }

    void Resource::set_authentication_handler( const function< void ( const Request&, Response& ) >& value )
    {
        m_pimpl->set_authentication_handler( value );
    }
    
    void Resource::set_error_handler( const function< void ( const int, const Request&, Response& ) >& value )
    {
        m_pimpl->set_error_handler( value );
    }
    
    Resource& Resource::operator =( const Resource& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }

    bool Resource::operator >( const Resource& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }

    bool Resource::operator <( const Resource& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }
    
    bool Resource::operator ==( const Resource& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }
    
    bool Resource::operator !=( const Resource& value ) const
    {
        return *m_pimpl not_eq *value.m_pimpl;
    }
}
