/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_URI_H
#define _RESTBED_URI_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

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
            static const bool Relative = true;
            static const bool Absolute = false;
            
            //Constructors
            explicit Uri( const std::string& value, bool relative = false );
            
            Uri( const Uri& original );
            
            virtual ~Uri( void );
            
            //Functionality
            bool is_relative( void ) const;
            
            bool is_absolute( void ) const;
            
            std::string to_string( void ) const;
            
            static bool is_valid( const std::string& value );
            
            static Uri parse( const std::string& value );
            
            static std::string decode( const Bytes& value );
            
            static std::string decode( const std::string& value );
            
            static std::string decode_parameter( const std::string& value );
            
            static std::string encode( const Bytes& value );
            
            static std::string encode( const std::string& value );
            
            static std::string encode_parameter( const std::string& value );
            
            //Getters
            uint16_t get_port( void ) const;
            
            std::string get_path( void ) const;
            
            std::string get_query( void ) const;
            
            std::string get_scheme( void ) const;
            
            std::string get_fragment( void ) const;
            
            std::string get_username( void ) const;
            
            std::string get_password( void ) const;
            
            std::string get_authority( void ) const;
            
            std::multimap< std::string, std::string > get_query_parameters( void ) const;
            
            //Setters
            
            //Operators
            Uri& operator =( const Uri& rhs );
            
            bool operator <( const Uri& rhs ) const;
            
            bool operator >( const Uri& rhs ) const;
            
            bool operator ==( const Uri& rhs ) const;
            
            bool operator !=( const Uri& rhs ) const;
            
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

#endif  /* _RESTBED_URI_H */
