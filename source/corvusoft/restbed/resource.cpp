/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes

//Project Includes
#include "restbed/method.h"
#include "restbed/request.h"
#include "restbed/response.h"
#include "restbed/resource.h"
#include "restbed/detail/resource_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;

//Project Namespaces
using restbed::detail::ResourceImpl;

//External Namespaces

namespace restbed
{
    Resource::Resource( void ) : m_pimpl( new ResourceImpl )
    {
        //n/a
    }
    
    Resource::Resource( const Resource& original ) : m_pimpl( new ResourceImpl( *original.m_pimpl ) )
    {
        //n/a
    }
    
    Resource::~Resource( void )
    {
        //n/a
    }

    string Resource::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }

    string Resource::get_header_filter( const string& name ) const
    {
        return m_pimpl->get_header_filter( name );
    }

    map< string, string > Resource::get_header_filters( void ) const
    {
        return m_pimpl->get_header_filters( );
    }

    function< Response ( const Request& ) > Resource::get_method_handler( const Method& method ) const
    {
        return m_pimpl->get_method_handler( method );
    }

    void Resource::set_path( const string& value )
    {
        m_pimpl->set_path( value );
    }

    void Resource::set_header_filter( const string& name, const string& value )
    {
        m_pimpl->set_header_filter( name, value );
    }

    void Resource::set_method_handler( const Method& verb, const function< Response ( const Request& ) >& callback )
    {
        m_pimpl->set_method_handler( verb, callback );
    }

    bool Resource::operator <( const Resource& rhs ) const
    {
        return *m_pimpl < *rhs.m_pimpl;
    }
    
    bool Resource::operator >( const Resource& rhs ) const
    {
        return *m_pimpl > *rhs.m_pimpl;
    }
    
    bool Resource::operator ==( const Resource& rhs ) const
    {
        return *m_pimpl == *rhs.m_pimpl;
    }
    
    bool Resource::operator !=( const Resource& rhs ) const
    {
        return *m_pimpl != *rhs.m_pimpl;
    }

    Resource& Resource::operator =( const Resource& rhs )
    {
        *m_pimpl = *rhs.m_pimpl;

        return *this;
    }
}
