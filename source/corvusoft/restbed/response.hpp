/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <limits>
#include <memory>
#include <cstdint>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/common.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define RESPONSE_EXPORT __declspec(dllexport)
	#else
		#define RESPONSE_EXPORT __declspec(dllimport)
	#endif
#else
	#define RESPONSE_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Http;
    
    namespace detail
    {
        struct ResponseImpl;
    }
    
    class Response
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            RESPONSE_EXPORT Response( void );
            
            RESPONSE_EXPORT virtual ~Response( void );
            
            //Functionality
            RESPONSE_EXPORT bool has_header( const std::string& name ) const;
            
            //Getters
            RESPONSE_EXPORT Bytes get_body( void ) const;
            
            RESPONSE_EXPORT double get_version( void ) const;
            
            RESPONSE_EXPORT int get_status_code( void ) const;
            
            RESPONSE_EXPORT std::string get_protocol( void ) const;
            
            RESPONSE_EXPORT std::string get_status_message( void ) const;
            
            RESPONSE_EXPORT void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
            Type get_header( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_header( name ), default_value );
            }
            
            RESPONSE_EXPORT std::string get_header( const std::string& name, const std::string& default_value ) const;
            
            RESPONSE_EXPORT std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            RESPONSE_EXPORT std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            //Setters
            RESPONSE_EXPORT void set_body( const Bytes& value );
            
            RESPONSE_EXPORT void set_body( const std::string& value );
            
            RESPONSE_EXPORT void set_version( const double value );
            
            RESPONSE_EXPORT void set_status_code( const int value );
            
            RESPONSE_EXPORT void set_protocol( const std::string& protocol );
            
            RESPONSE_EXPORT void set_status_message( const std::string& value );

            RESPONSE_EXPORT void add_header( const std::string& name, const std::string& value );

            RESPONSE_EXPORT void set_header( const std::string& name, const std::string& value );
            
            RESPONSE_EXPORT void set_headers( const std::multimap< std::string, std::string >& values );
            
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
            
            //Definitions
            
            //Constructors
            Response( const Response& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Response& operator =( const Response& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::ResponseImpl > m_pimpl;
    };
}
