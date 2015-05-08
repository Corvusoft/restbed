/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/methods.h"
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/response.h"
#include "corvusoft/restbed/detail/resource_impl.h"

//External Includes
#include <corvusoft/framework/string>
#include <corvusoft/framework/unique_id>

//System Namespaces
using std::set;
using std::pair;
using std::string;
using std::function;
using std::multimap;
using std::invalid_argument;

//Project Namespaces

//External Namespaces
using framework::String;
using framework::UniqueId;

namespace restbed
{
    namespace detail
    {
        ResourceImpl::ResourceImpl( void ) : m_id( UniqueId::generate( ).to_string( ) ),
            m_paths( ),
            m_method_handlers( )
        {
            return;
        }
        
        ResourceImpl::ResourceImpl( const ResourceImpl& original ) : m_id( original.m_id ),
            m_paths( original.m_paths ),
            m_method_handlers( original.m_method_handlers )
        {
            return;
        }
        
        ResourceImpl::~ResourceImpl( void )
        {
            return;
        }

        const string& ResourceImpl::get_id( void ) const
        {
            return m_id;
        }
        
        const set< string >& ResourceImpl::get_paths( void ) const
        {
            return m_paths;
        }
        
        multimap< string, pair< multimap< string, string >, function< Response ( const Request& ) > > >
        ResourceImpl::get_method_handlers( const string& method ) const
        {
            //this return argument stinks
            if ( method.empty( ) )
            {
                return m_method_handlers;
            }

            const string verb = String::uppercase( method );

            if ( m_method_handlers.count( verb ) == 0 )
            {
                throw invalid_argument(
                    String::format( "Resource has no handler associated with HTTP method '%s'.", verb.data( ) )
                );
            }

            return decltype( m_method_handlers )( m_method_handlers.lower_bound( verb ),
                                                  m_method_handlers.upper_bound( verb ) );
        }
        
        void ResourceImpl::set_paths( const set< string >& values )
        {
            m_paths = values;
        }
        
        void ResourceImpl::set_method_handler( const string& method,
                                               const multimap< string, string >& filters,
                                               const function< Response ( const Request& ) >& callback )
        {
            const string verb = String::uppercase( method );

            if ( methods.count( verb ) == 0 )
            {
                throw invalid_argument(
                    String::format( "Resource method handler set with an unsupported HTTP method '%s'.", verb.data( ) )
                );
            }
            
            m_method_handlers.insert( make_pair( verb, make_pair( filters, callback ) ) );
        }

        void ResourceImpl::set_authentication_handler( const function< void ( const Request&, Response& ) >& value )
        {
            //m_authentication_handler = value;
        }

        void ResourceImpl::set_error_handler( const function< void ( const int, const Request&, Response& ) >& value )
        {
            //m_error_handler = value;
        }
        
        bool ResourceImpl::operator >( const ResourceImpl& value ) const
        {
            return UniqueId( m_id ) > UniqueId( value.m_id );
        }

        bool ResourceImpl::operator <( const ResourceImpl& value ) const
        {
            return UniqueId( m_id ) < UniqueId( value.m_id );
        }

        bool ResourceImpl::operator ==( const ResourceImpl& value ) const
        {
            return m_id == value.m_id;
        }
        
        bool ResourceImpl::operator !=( const ResourceImpl& value ) const
        {
            return m_id not_eq value.m_id;
        }
        
        ResourceImpl& ResourceImpl::operator =( const ResourceImpl& value )
        {
            m_id = value.m_id;

            m_paths = value.m_paths;

            m_method_handlers = value.m_method_handlers;
            
            return *this;
        }
    }
}
