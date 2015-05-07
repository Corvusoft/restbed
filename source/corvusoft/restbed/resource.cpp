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
using std::map;
using std::vector;
using std::string;
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
    
    Resource::Resource( const ResourceImpl& implementation ) : m_pimpl( new ResourceImpl( implementation ) )
    {
        return;
    }
    
    Resource::~Resource( void )
    {
        return;
    }
    
    string Resource::get_path( void ) const
    {
        return m_pimpl->get_path( );
    }

    vector< string > Resource::get_paths( void ) const
    {
        return m_pimpl->get_paths( );
    }
    
    string Resource::get_header_filter( const string& name ) const
    {
        return m_pimpl->get_header_filter( name );
    }
    
    map< string, string > Resource::get_header_filters( void ) const
    {
        return m_pimpl->get_header_filters( );
    }
    
    function< Response ( const Request& ) > Resource::get_method_handler( const string& method ) const
    {
        return m_pimpl->get_method_handler( method );
    }
    
    map< string, function< Response ( const Request& ) > > Resource::get_method_handlers( void ) const
    {
        return m_pimpl->get_method_handlers( );
    }
    
    void Resource::set_path( const string& value )
    {
        m_pimpl->set_path( value );
    }

    void Resource::set_paths( const vector< string >& values )
    {
        m_pimpl->set_paths( values );
    }
    
    void Resource::set_header_filter( const string& name, const string& value )
    {
        m_pimpl->set_header_filter( name, value );
    }
    
    void Resource::set_header_filters( const map< string, string >& values )
    {
        m_pimpl->set_header_filters( values );
    }
    
    void Resource::set_method_handler( const string& method, const function< Response ( const Request& ) >& callback )
    {
        m_pimpl->set_method_handler( method, callback );
    }
    
    void Resource::set_method_handlers( const map< string, function< Response ( const Request& ) > >& values )
    {
        m_pimpl->set_method_handlers( values );
    }
    
    Resource& Resource::operator =( const Resource& value )
    {
        *m_pimpl = *value.m_pimpl;
        
        return *this;
    }
    
    bool Resource::operator <( const Resource& value ) const
    {
        return *m_pimpl < *value.m_pimpl;
    }
    
    bool Resource::operator >( const Resource& value ) const
    {
        return *m_pimpl > *value.m_pimpl;
    }
    
    bool Resource::operator ==( const Resource& value ) const
    {
        return *m_pimpl == *value.m_pimpl;
    }
    
    bool Resource::operator !=( const Resource& value ) const
    {
        return *m_pimpl != *value.m_pimpl;
    }
}
