/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

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
        //Forward Declarations
        
        class RequestImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                RequestImpl( void );
                
                RequestImpl( const RequestImpl& original );
                
                virtual ~RequestImpl( void );
                
                //Functionality
                framework::Bytes to_bytes( void ) const;
                
                bool has_header( const std::string& name ) const;
                
                bool has_path_parameter( const std::string& name ) const;
                
                bool has_query_parameter( const std::string& name ) const;
                
                //Getters
                framework::Bytes get_body( void ) const;
                
                double get_version( void ) const;
                
                std::string get_path( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_origin( void ) const;
                
                std::string get_header( const std::string& name, const std::string& default_value ) const;
                
                std::map< std::string, std::string > get_headers( void ) const;
                
                std::string get_query_parameter( const std::string& name, const std::string& default_value ) const;
                
                std::multimap< std::string, std::string > get_query_parameters( void ) const;
            
                std::multimap< std::string, std::string > get_query_parameters( const std::string& name ) const;
                
                std::string get_path_parameter( const std::string& name, const std::string& default_value ) const;
                
                std::map< std::string, std::string > get_path_parameters( void ) const;
                
                //Setters
                void set_body( const framework::Bytes& value );
                
                void set_version( const double value );
                
                void set_path( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_origin( const std::string& value );
                
                void set_headers( const std::map< std::string, std::string >& values );
                
                void set_path_parameters( const std::map< std::string, std::string >& values );
                
                void set_query_parameters( const std::multimap< std::string, std::string >& values );
                
                //Operators
                bool operator <( const RequestImpl& value ) const;
                
                bool operator >( const RequestImpl& value ) const;
                
                bool operator ==( const RequestImpl& value ) const;
                
                bool operator !=( const RequestImpl& value ) const;
                
                RequestImpl& operator =( const RequestImpl& value );
                
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
                std::string generate_status_section( void ) const;
                
                std::string generate_header_section( void ) const;
                
                std::string generate_path_section( void ) const;
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                framework::Bytes m_body;
                
                double m_version;
                
                std::string m_path;
                
                std::string m_method;
                
                std::string m_origin;
                
                std::map< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::multimap< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
