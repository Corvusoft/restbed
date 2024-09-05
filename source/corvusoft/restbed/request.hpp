/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <limits>
#include <string>
#include <memory>
#include <cstdint>
#include <stdexcept>
#include <functional>
#include <type_traits>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/common.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define REQUEST_EXPORT __declspec(dllexport)
	#else
		#define REQUEST_EXPORT __declspec(dllimport)
	#endif
#else
	#define REQUEST_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Http;
    class Session;
    class Response;
    
    namespace detail
    {
        class HttpImpl;
        class SessionImpl;
        class ServiceImpl;
        struct RequestImpl;
        class WebSocketManagerImpl;
    }
    
    class Request
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            REQUEST_EXPORT Request( void );
            
            REQUEST_EXPORT Request( const Uri& value );
            
            REQUEST_EXPORT virtual ~Request( void );
            
            //Functionality
            REQUEST_EXPORT bool has_header( const std::string& name ) const;
            
            REQUEST_EXPORT bool has_path_parameter( const std::string& name ) const;
            
            REQUEST_EXPORT bool has_query_parameter( const std::string& name ) const;
            
            //Getters
            REQUEST_EXPORT uint16_t get_port( void ) const;
            
            REQUEST_EXPORT double get_version( void ) const;
            
            REQUEST_EXPORT const Bytes& get_body( void ) const;
            
            REQUEST_EXPORT const std::shared_ptr< const Response > get_response( void ) const;
            
            REQUEST_EXPORT std::string get_host( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            REQUEST_EXPORT std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            REQUEST_EXPORT std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            REQUEST_EXPORT std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            REQUEST_EXPORT void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            REQUEST_EXPORT std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
            
            REQUEST_EXPORT std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template <typename Type, std::enable_if_t< std::is_arithmetic< std::remove_reference_t< Type > >::value > * = nullptr> inline
            Type get_header( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_header( name ), default_value );
            }
            
            REQUEST_EXPORT std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            REQUEST_EXPORT std::string get_query_parameter( const std::string& name, const std::string& default_value = "" ) const;
            
            REQUEST_EXPORT std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template <typename Type, std::enable_if_t< std::is_arithmetic< std::remove_reference_t< Type > >::value > * = nullptr> inline
            Type get_query_parameter( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_query_parameter( name ), default_value );
            }
            
            REQUEST_EXPORT std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "" ) const;
            
            REQUEST_EXPORT std::string get_path_parameter( const std::string& name, const std::string& default_value = "" ) const;
            
            REQUEST_EXPORT std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template <typename Type, std::enable_if_t< std::is_arithmetic< std::remove_reference_t< Type > >::value > * = nullptr> inline
            Type get_path_parameter( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_path_parameter( name ), default_value );
            }
            
            REQUEST_EXPORT std::map< std::string, std::string > get_path_parameters( const std::string& name = "" ) const;
            
            //Setters
            REQUEST_EXPORT void set_body( const Bytes& value );
            
            REQUEST_EXPORT void set_body( const std::string& value );
            
            REQUEST_EXPORT void set_port( const uint16_t value );
            
            REQUEST_EXPORT void set_version( const double value );
            
            REQUEST_EXPORT void set_path( const std::string& value );
            
            REQUEST_EXPORT void set_host( const std::string& value );
            
            REQUEST_EXPORT void set_method( const std::string& value );
            
            REQUEST_EXPORT void set_protocol( const std::string& value );
            
            REQUEST_EXPORT void add_header( const std::string& name, const std::string& value );
            
            REQUEST_EXPORT void set_header( const std::string& name, const std::string& value );
            
            REQUEST_EXPORT void set_headers( const std::multimap< std::string, std::string >& values );
            
            REQUEST_EXPORT void set_query_parameter( const std::string& name, const std::string& value );
            
            REQUEST_EXPORT void set_query_parameters( const std::multimap< std::string, std::string >& values );
            
            //Operators
            
            //Properties
            
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
            friend Http;
            friend Session;
            friend detail::HttpImpl;
            friend detail::SessionImpl;
            friend detail::ServiceImpl;
            friend detail::WebSocketManagerImpl;
            
            //Definitions
            
            //Constructors
            Request( const Request& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Request& operator =( const Request& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::RequestImpl > m_pimpl;
    };
}
