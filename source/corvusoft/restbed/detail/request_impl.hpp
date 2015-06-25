/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/byte>
#include <corvusoft/framework/string>

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
                
                virtual ~RequestImpl( void );
                
                //Functionality
                bool has_header( const std::string& name ) const;
                
                bool has_path_parameter( const std::string& name, const bool ignore_case ) const;
                
                bool has_query_parameter( const std::string& name, const bool ignore_case ) const;
                
                //Getters
                double get_version( void ) const;
                
                const std::string get_path( const std::function< std::string ( const std::string& ) >& transform ) const;
                
                const std::string get_method( const std::function< std::string ( const std::string& ) >& transform ) const;
                
                const std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform ) const;
                
                const framework::Bytes get_body( const std::function< framework::Bytes ( const framework::Bytes& ) >& transform ) const;
                
                void get_body( std::string& body, const std::function< framework::Bytes ( const framework::Bytes& ) >& transform ) const;
                
                void get_header( const std::string& name, int& value, const int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_header( const std::string& name, unsigned int& value, const unsigned int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_header( const std::string& name, long& value, const long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_header( const std::string& name, unsigned long& value, const unsigned long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_header( const std::string& name, float& value, const float default_value, const std::function< std::string ( const std::string& ) > transform ) const;
                
                void get_header( const std::string& name, double& value, const double default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::string get_header( const std::string& name, const std::string& default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::multimap< std::string, std::string > get_headers( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_query_parameter( const std::string& name, int& value, const int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_query_parameter( const std::string& name, unsigned int& value, const unsigned int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_query_parameter( const std::string& name, long& value, const long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_query_parameter( const std::string& name, unsigned long& value, const unsigned long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_query_parameter( const std::string& name, float& value, const float default_value, const std::function< std::string ( const std::string& ) > transform ) const;
                
                void get_query_parameter( const std::string& name, double& value, const double default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::string get_query_parameter( const std::string& name, const std::string& default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::multimap< std::string, std::string > get_query_parameters( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_path_parameter( const std::string& name, int& value, const int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_path_parameter( const std::string& name, unsigned int& value, const unsigned int default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_path_parameter( const std::string& name, long& value, const long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_path_parameter( const std::string& name, unsigned long& value, const unsigned long default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                void get_path_parameter( const std::string& name, float& value, const float default_value, const std::function< std::string ( const std::string& ) > transform ) const;
                
                void get_path_parameter( const std::string& name, double& value, const double default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::string get_path_parameter( const std::string& name, const std::string& default_value, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                std::map< std::string, std::string > get_path_parameters( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
                
                //Setters
                void set_version( const double value );
                
                void set_path( const std::string& value );
                
                void set_method( const std::string& value );
                
                void set_protocol( const std::string& value );
                
                void set_body( const framework::Bytes& value );
                
                void set_headers( const std::multimap< std::string, std::string >& values );
                
                void set_path_parameter( const std::string& name, const std::string& value );
                
                void set_query_parameters( const std::multimap< std::string, std::string >& values );
                
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
                RequestImpl( const RequestImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                RequestImpl& operator =( const RequestImpl& value ) = delete;
                
                //Properties
                double m_version;
                
                std::string m_path;
                
                std::string m_method;
                
                std::string m_protocol;
                
                framework::Bytes m_body;
                
                std::multimap< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::multimap< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
