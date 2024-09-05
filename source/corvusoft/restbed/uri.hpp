/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <memory>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define URI_EXPORT __declspec(dllexport)
	#else
		#define URI_EXPORT __declspec(dllimport)
	#endif
#else
	#define URI_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    namespace detail
    {
		struct UriImpl;
    }
    
    class Uri
    {
        public:
            //Friends
            
            //Definitions
            URI_EXPORT static const bool Relative = true;
            URI_EXPORT static const bool Absolute = false;
            
            //Constructors
            URI_EXPORT explicit Uri( const std::string& value, bool relative = false );
            
            URI_EXPORT Uri( const Uri& original );
            
            URI_EXPORT virtual ~Uri( void );
            
            //Functionality
            URI_EXPORT bool is_relative( void ) const;
            
            URI_EXPORT bool is_absolute( void ) const;
            
            URI_EXPORT std::string to_string( void ) const;
            
            URI_EXPORT static bool is_valid( const std::string& value );
            
            URI_EXPORT static Uri parse( const std::string& value );
            
            URI_EXPORT static std::string decode( const Bytes& value );
            
            URI_EXPORT static std::string decode( const std::string& value );
        
            URI_EXPORT static std::string decode_parameter( const std::string& value );
            
            URI_EXPORT static std::string encode( const Bytes& value );
            
            URI_EXPORT static std::string encode( const std::string& value );
            
            URI_EXPORT static std::string encode_parameter( const std::string& value );
            
            //Getters
            URI_EXPORT uint16_t get_port( void ) const;
            
            URI_EXPORT std::string get_path( void ) const;
            
            URI_EXPORT std::string get_query( void ) const;
            
            URI_EXPORT std::string get_scheme( void ) const;
            
            URI_EXPORT std::string get_fragment( void ) const;
            
            URI_EXPORT std::string get_username( void ) const;
            
            URI_EXPORT std::string get_password( void ) const;
            
            URI_EXPORT std::string get_authority( void ) const;
            
            URI_EXPORT std::multimap< std::string, std::string > get_query_parameters( void ) const;
            
            //Setters
            
            //Operators
            URI_EXPORT Uri& operator =( const Uri& rhs );
            
            URI_EXPORT bool operator <( const Uri& rhs ) const;
            
            URI_EXPORT bool operator >( const Uri& rhs ) const;
            
            URI_EXPORT bool operator ==( const Uri& rhs ) const;
            
            URI_EXPORT bool operator !=( const Uri& rhs ) const;
            
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
            
            //Definitions
            
            //Constructors
            Uri( void );
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            std::unique_ptr< detail::UriImpl > m_pimpl;
    };
}
