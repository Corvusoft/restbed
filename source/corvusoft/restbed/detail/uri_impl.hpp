/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_URI_IMPL_H
#define _RESTBED_DETAIL_URI_IMPL_H 1

//System Includes
#include <map>
#include <string>

//Project Includes
#include "corvusoft/restbed/byte.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class UriImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                UriImpl( void );
                
                UriImpl( const std::string& value );
                
                UriImpl( const UriImpl& original );
                
                virtual ~UriImpl( void );
                
                //Functionality
                std::string to_string( void ) const;

                static bool is_valid( const std::string& value );
                
                static std::string decode( const Bytes& value );
                
                static std::string decode( const std::string& value );
                
                static std::string decode_parameter( const std::string& value );
                
                static std::string encode( const Bytes& value );
                
                static std::string encode( const std::string& value );
                
                //Getters
                int get_port( void ) const;
                
                std::string get_path( void ) const;
                
                std::string get_query( void ) const;
                
                std::string get_scheme( void ) const;
                
                std::string get_fragment( void ) const;
                
                std::string get_username( void ) const;
                
                std::string get_password( void ) const;
                
                std::string get_authority( void ) const;

                std::multimap< std::string, std::string > get_query_parameters( void ) const;

                //Setters
                void set_uri( const std::string& value );
                
                //Operators
                UriImpl& operator =( const UriImpl& rhs );
                
                bool operator <( const UriImpl& rhs ) const;
                
                bool operator >( const UriImpl& rhs ) const;
                
                bool operator ==( const UriImpl& rhs ) const;
                
                bool operator !=( const UriImpl& rhs ) const;
                
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
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::string m_uri;
        };
    }
}

#endif  /* _RESTBED_DETAIL_URI_IMPL_H */
