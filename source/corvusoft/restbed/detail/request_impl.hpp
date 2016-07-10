/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <utility>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/string.hpp>

//External Includes
#include <asio/streambuf.hpp>
#include <asio/io_service.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Response;
    
    namespace detail
    {
        //Forward Declarations
        
        class RequestImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                RequestImpl( void );
                
                RequestImpl( const RequestImpl& original ) = delete;
                
                virtual ~RequestImpl( void );
                
                //Functionality
                template< typename Type >
                Type get_parameters( const std::string& name, const Type& parameters ) const
                {
                    if ( name.empty( ) )
                    {
                        return parameters;
                    }
                    
                    const auto key = String::lowercase( name );
                    Type results;
                    
                    for ( const auto& parameter : parameters )
                    {
                        if ( key == String::lowercase( parameter.first ) )
                        {
                            results.insert( parameter );
                        }
                    }
                    
                    return results;
                }
                
                template< typename Type >
                bool has_parameter( const std::string& name, const Type& parameters ) const
                {
                    const auto key = String::lowercase( name );
                    const auto iterator = std::find_if( parameters.begin( ), parameters.end( ), [ &key ]( const std::pair< std::string, std::string >& value )
                    {
                        return ( key == String::lowercase( value.first ) );
                    } );
                    
                    return iterator not_eq parameters.end( );
                }
                
                static std::string transform( const std::string& value, const std::function< std::string ( const std::string& ) >& transform )
                {
                    return ( transform == nullptr ) ? value : transform( value );
                }
                
                //Getters
                
                //Setters
                
                //Operators
                RequestImpl& operator =( const RequestImpl& value ) = delete;
                
                //Properties
                Bytes m_body { };
                
                uint16_t m_port;
                
                double m_version;
                
                std::string m_host;
                
                std::string m_path;
                
                std::string m_method;
                
                std::string m_protocol;
                
                std::shared_ptr< Uri > m_uri;
                
                std::shared_ptr< Response > m_response;
                
                std::multimap< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::multimap< std::string, std::string > m_query_parameters;
                
                std::shared_ptr< asio::io_service > m_io_service;
                
                std::shared_ptr< SocketImpl > m_socket;
                
                std::shared_ptr< asio::streambuf > m_buffer;
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
