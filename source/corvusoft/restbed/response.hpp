/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_RESPONSE_H
#define _RESTBED_RESPONSE_H 1

//System Includes
#include <map>
#include <string>

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
        struct ResponseImpl;
    }
    
    class Response
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Response( void );
            
            virtual ~Response( void );
            
            //Functionality
            Bytes to_bytes( void ) const;
            
            //Getters
            Bytes get_body( void ) const;
            
            double get_version( void ) const;
            
            int get_status_code( void ) const;
            
            std::string get_protocol( void ) const;
            
            std::string get_status_message( void ) const;
            
            std::multimap< std::string, std::string > get_headers( void ) const;
            
            //Setters
            void set_body( const Bytes& value );

            void set_body( const std::string& value );

            void set_version( const double value );

            void set_status_code( const int value );
            
            void set_protocol( const std::string& protocol );
            
            void set_status_message( const std::string& value );
            
            void set_header( const std::string& name, const std::string& value );
            
            void set_headers( const std::multimap< std::string, std::string >& values );
            
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
            
            //Definitions
            
            //Constructors
            Response( const Response& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Response& operator =( const Response& value ) = delete;
            
            //Properties
            detail::ResponseImpl* m_pimpl;
    };
}

#endif  /* _RESTBED_RESPONSE_H */
