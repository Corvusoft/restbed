/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/string.hpp"
#include "corvusoft/restbed/detail/response_impl.hpp"

//External Includes

//System Namespaces
using std::string;
using std::multimap;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        ResponseImpl::ResponseImpl( void ) : m_version( 1.1 ),
            m_status_code( 200 ),
            m_protocol( "HTTP" ),
            m_body( ),
            m_status_message( "" ),
            m_headers( )
        {
            return;
        }
        
        ResponseImpl::~ResponseImpl( void )
        {
            return;
        }
        
        Bytes ResponseImpl::to_bytes( void ) const
        {
            auto data = String::format( "%s/%.1f %i %s\r\n", m_protocol.data( ), m_version, m_status_code, m_status_message.data( ) );
            
            if ( not m_headers.empty( ) )
            {
                const auto headers = String::join( m_headers, ": ", "\r\n" );
                data += headers + "\r\n";
            }
            
            data += "\r\n";
            
            Bytes bytes = String::to_bytes( data );
            
            if ( not m_body.empty( ) )
            {
                bytes.insert( bytes.end( ), m_body.begin( ), m_body.end( ) );
            }
            
            return bytes;
        }
        
        double ResponseImpl::get_version( void ) const
        {
            return m_version;
        }
        
        int ResponseImpl::get_status_code( void ) const
        {
            return m_status_code;
        }
        
        const Bytes& ResponseImpl::get_body( void ) const
        {
            return m_body;
        }
        
        const string& ResponseImpl::get_protocol( void ) const
        {
            return m_protocol;
        }
        
        const string& ResponseImpl::get_status_message( void ) const
        {
            return m_status_message;
        }
        
        const multimap< string, string >& ResponseImpl::get_headers( void ) const
        {
            return m_headers;
        }
        
        void ResponseImpl::set_version( const double value )
        {
            m_version = value;
        }
        
        void ResponseImpl::set_status_code( const int value )
        {
            m_status_code = value;
        }
        
        void ResponseImpl::set_protocol( const string& value )
        {
            m_protocol = value;
        }
        
        void ResponseImpl::set_body( const Bytes& value )
        {
            m_body = value;
        }
        
        void ResponseImpl::set_status_message( const string& value )
        {
            m_status_message = value;
        }
        
        void ResponseImpl::set_header( const string& name, const string& value )
        {
            m_headers.insert( make_pair( name, value ) );
        }
        
        void ResponseImpl::set_headers( const multimap< string, string >& values )
        {
            m_headers = values;
        }
    }
}
