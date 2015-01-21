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
#include <corvusoft/framework/bytes>

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
            
            Response( const Response& original );
        
            Response( const detail::ResponseImpl& implementation );
            
            virtual ~Response( void );
            
            //Functionality
            framework::Bytes to_bytes( void ) const;
            
            //Getters
            framework::Bytes get_body( void ) const;
        
            double get_version( void ) const;
        
            int get_status_code( void ) const;
        
            std::string get_status_message( void ) const;
        
            std::string get_header( const std::string& name ) const;
            
            std::map< std::string, std::string > get_headers( void ) const;
            
            //Setters
            void set_body( const framework::Bytes& value );
            
            void set_body( const std::string& value );
        
            void set_version( const double value );
            
            void set_status_code( const int value );
        
            void set_status_message( const std::string& value );
        
            void set_header( const std::string& name, const std::string& value );
            
            void set_headers( const std::map< std::string, std::string >& values );
            
            //Operators
            Response& operator =( const Response& value );
            
            bool operator <( const Response& value ) const;
            
            bool operator >( const Response& value ) const;
            
            bool operator ==( const Response& value ) const;
            
            bool operator !=( const Response& value ) const;
            
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
            std::unique_ptr< detail::ResponseImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_RESPONSE_H */
