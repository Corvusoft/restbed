/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <istream>

//Project Includes
#include <corvusoft/restbed/bytes>

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
                Bytes to_bytes( void ) const;

                bool has_header( const std::string& name ) const;

                bool has_path_parameter( const std::string& name ) const;

                bool has_query_parameter( const std::string& name ) const;
                
                //Getters
                double get_version( void ) const;

                std::string get_path( void ) const;

                std::string get_body( void ) const;
                
                std::string get_method( void ) const;
                
                std::string get_header( const std::string& name ) const;
                
                std::map< std::string, std::string > get_headers( void ) const;
                
                std::string get_query_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_query_parameters( void ) const;
                
                std::string get_path_parameter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_path_parameters( void ) const;
                
                //Setters
                void set_version( const double value );

                void set_path( const std::string& value );

                void set_body( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_headers( const std::map< std::string, std::string >& values );
                
                void set_path_parameters( const std::map< std::string, std::string >& values );

                void set_query_parameters( const std::map< std::string, std::string >& values );

                //Operators
                bool operator <( const RequestImpl& rhs ) const;
                
                bool operator >( const RequestImpl& rhs ) const;
                
                bool operator ==( const RequestImpl& rhs ) const;
                
                bool operator !=( const RequestImpl& rhs ) const;
                
                RequestImpl& operator =( const RequestImpl& rhs );
                
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

                double m_version;

                std::string m_path;

                std::string m_body;
                
                std::string m_method;
                
                std::map< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::map< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
