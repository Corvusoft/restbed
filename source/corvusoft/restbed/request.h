/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

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
        class RequestImpl;
    }
    
    class Request
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Request( void );
            
            Request( const Request& original );
        
            Request( const detail::RequestImpl& implementation );
            
            virtual ~Request( void );
            
            //Functionality            
            bool has_header( const std::string& name ) const;
            
            bool has_path_parameter( const std::string& name ) const;
            
            bool has_query_parameter( const std::string& name ) const;
            
            //Getters
            framework::Bytes get_body( void ) const;

            framework::Bytes get_body( const std::size_t length ) const;

            framework::Bytes get_body( const std::string& delimiter ) const;
            
            double get_version( void ) const;

            std::string get_method( void ) const;
            
            std::string get_path( void ) const;
            
            std::string get_origin( void ) const;

            std::string get_destination( void ) const;
        
            std::string get_protocol( void ) const;
            
            std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
            
            std::multimap< std::string, std::string > get_headers( void ) const;
        
            std::multimap< std::string, std::string > get_headers( const std::string& name ) const;
            
            std::string get_query_parameter( const std::string& name, const std::string& default_value = ""  ) const;
        
            std::multimap< std::string, std::string > get_query_parameters( void ) const;
        
            std::multimap< std::string, std::string > get_query_parameters( const std::string& name ) const;
            
            std::string get_path_parameter( const std::string& name, const std::string& default_value = ""  ) const;
            
            std::map< std::string, std::string > get_path_parameters( void ) const;
            
            //Setters
            
            //Operators
            Request& operator =( const Request& value );
            
            bool operator <( const Request& value ) const;
            
            bool operator >( const Request& value ) const;
            
            bool operator ==( const Request& value ) const;
            
            bool operator !=( const Request& value ) const;
            
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
            std::unique_ptr< detail::RequestImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_REQUEST_H */
