/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <istream>

//Project Includes

//External Includes
#include <corvusoft/framework/bytes>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Method;
    
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
            
            virtual ~Request( void );
            
            //Functionality
            framework::Bytes to_bytes( void ) const;
            
            bool has_header( const std::string& name ) const;
            
            bool has_path_parameter( const std::string& name ) const;
            
            bool has_query_parameter( const std::string& name ) const;
            
            //Getters
            framework::Bytes get_body( void ) const;
            
            Method get_method( void ) const;
            
            double get_version( void ) const;
            
            std::string get_path( void ) const;
            
            std::string get_origin( void ) const;
            
            std::string get_header( const std::string& name ) const;
            
            std::map< std::string, std::string > get_headers( void ) const;
            
            std::string get_query_parameter( const std::string& name ) const;
            
            std::map< std::string, std::string > get_query_parameters( void ) const;
            
            std::string get_path_parameter( const std::string& name ) const;
            
            std::map< std::string, std::string > get_path_parameters( void ) const;
            
            //Setters
            
            //Operators
            Request& operator =( const Request& rhs );
            
            bool operator <( const Request& rhs ) const;
            
            bool operator >( const Request& rhs ) const;
            
            bool operator ==( const Request& rhs ) const;
            
            bool operator !=( const Request& rhs ) const;
            
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
            std::unique_ptr< detail::RequestImpl > m_pimpl;
            
        private:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
    };
}

#endif  /* _RESTBED_REQUEST_H */
