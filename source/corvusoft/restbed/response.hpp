/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_RESPONSE_H
#define _RESTBED_RESPONSE_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <cstdint>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Http;
    class Request;
    
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
            bool has_header( const std::string& name ) const;
            
            //Getters
            Bytes get_body( void ) const;
            
            double get_version( void ) const;
            
            int get_status_code( void ) const;
            
            std::string get_protocol( void ) const;
            
            std::string get_status_message( void ) const;
            
            const std::shared_ptr< const Request > get_request( void ) const;
            
            void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            void get_header( const std::string& name, int& value, const int default_value = 0 ) const;
            
            void get_header( const std::string& name, long& value, const long default_value = 0 ) const;
            
            void get_header( const std::string& name, float& value, const float default_value = 0 ) const;
            
            void get_header( const std::string& name, double& value, const double default_value = 0 ) const;
            
            void get_header( const std::string& name, long long& value, const long long default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;
            
            std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
            
            std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
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
            detail::ResponseImpl* m_pimpl;
    };
}

#endif  /* _RESTBED_RESPONSE_H */
