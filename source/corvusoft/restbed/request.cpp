/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.hpp"
#include "corvusoft/restbed/detail/request_impl.hpp"

//External Includes

//System Namespaces
using std::map;
using std::string;
using std::function;
using std::multimap;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::RequestImpl;

//External Namespaces

namespace restbed
{
    Request::Request( void ) : m_pimpl( new RequestImpl )
    {
        return;
    }
    
    Request::~Request( void )
    {
        return;
    }
    
    bool Request::has_header( const string& name ) const
    {
        return m_pimpl->has_header( name );
    }
    
    bool Request::has_path_parameter( const string& name, const bool ignore_case ) const
    {
        return m_pimpl->has_path_parameter( name, ignore_case );
    }
    
    bool Request::has_query_parameter( const string& name, const bool ignore_case ) const
    {
        return m_pimpl->has_query_parameter( name, ignore_case );
    }
    
    double Request::get_version( void ) const
    {
        return m_pimpl->get_version( );
    }
    
    const string Request::get_path( const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_path( transform );
    }
    
    const string Request::get_method( const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_method( transform );
    }
    
    const string Request::get_protocol( const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_protocol( transform );
    }
    
    const Bytes Request::get_body( const function< Bytes ( const Bytes& ) >& transform ) const
    {
        return m_pimpl->get_body( transform );
    }
    
    void Request::get_body( string& body, const function< Bytes ( const Bytes& ) >& transform ) const
    {
        return m_pimpl->get_body( body, transform );
    }
    
    void Request::get_header( const string& name, int& value, const int default_value, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    void Request::get_header( const string& name, unsigned int& value, const unsigned int default_value, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    void Request::get_header( const string& name, long& value, const long default_value, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    void Request::get_header( const string& name, unsigned long& value, const unsigned long default_value, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    void Request::get_header( const string& name, float& value, const float default_value, const function< string ( const string& ) > transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    void Request::get_header( const string& name, double& value, const double default_value, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_header( name, value, default_value, transform );
    }
    
    string Request::get_header( const string& name, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_header( name, "", transform );
    }
    
    string Request::get_header( const string& name, const string& default_value, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_header( name, default_value, transform );
    }
    
    multimap< string, string > Request::get_headers( const string& name, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_headers( name, transform );
    }
    
    void Request::get_query_parameter( const string& name, int& value, const int default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_query_parameter( const string& name, unsigned int& value, const unsigned int default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_query_parameter( const string& name, long& value, const long default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_query_parameter( const string& name, unsigned long& value, const unsigned long default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_query_parameter( const string& name, float& value, const float default_value, const bool ignore_case, const function< string ( const string& ) > transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_query_parameter( const string& name, double& value, const double default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_query_parameter( name, value, default_value, ignore_case, transform );
    }
    
    string Request::get_query_parameter( const string& name, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_query_parameter( name, "", ignore_case, transform );
    }
    
    string Request::get_query_parameter( const string& name, const string& default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_query_parameter( name, default_value, ignore_case, transform );
    }
    
    multimap< string, string > Request::get_query_parameters( const string& name, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_query_parameters( name, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, int& value, const int default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, unsigned int& value, const unsigned int default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, long& value, const long default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, unsigned long& value, const unsigned long default_value, const bool ignore_case, const function< string ( const string& ) >& transform  ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, float& value, const float default_value, const bool ignore_case, const function< string ( const string& ) > transform ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    void Request::get_path_parameter( const string& name, double& value, const double default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        m_pimpl->get_path_parameter( name, value, default_value, ignore_case, transform );
    }
    
    string Request::get_path_parameter( const string& name, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_path_parameter( name, "", ignore_case, transform );
    }
    
    string Request::get_path_parameter( const string& name, const string& default_value, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_path_parameter( name, default_value, ignore_case, transform );
    }
    
    map< string, string > Request::get_path_parameters( const string& name, const bool ignore_case, const function< string ( const string& ) >& transform ) const
    {
        return m_pimpl->get_path_parameters( name, ignore_case, transform );
    }
}
