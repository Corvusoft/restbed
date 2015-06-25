/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_RESPONSE_H
#define _RESTBED_RESPONSE_H 1

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes

//External Includes
#include <corvusoft/framework/byte>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    namespace detail
    {
        class ResponseImpl;
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
            framework::Bytes to_bytes( void ) const;
            
            //Getters
            double get_version( void ) const;
            
            int get_status_code( void ) const;
            
            framework::Bytes get_body( void ) const;
            
            std::string get_protocol( void ) const;
            
            std::string get_status_message( void ) const;
            
            std::multimap< std::string, std::string > get_headers( void ) const;
            
            //Setters
            void set_version( const double value );
            
            void set_protocol( const std::string& protocol );
            
            void set_status_code( const int value );
            
            void set_status_message( const std::string& value );
            
            void set_body( const std::string& value );
            
            void set_body( const framework::Bytes& value );
            
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
            std::unique_ptr< detail::ResponseImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_RESPONSE_H */
