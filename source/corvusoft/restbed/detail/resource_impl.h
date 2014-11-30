/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESOURCE_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <vector>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Method;
    class Request;
    class Response;
    
    namespace detail
    {
        //Forward Declarations
        
        class ResourceImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ResourceImpl( void );
                
                ResourceImpl( const ResourceImpl& original );
                
                virtual ~ResourceImpl( void );
                
                //Functionality
                
                //Getters
                std::string get_path( void ) const;
            
                std::vector< std::string > get_paths( void ) const;
                
                std::string get_header_filter( const std::string& name ) const;
                
                std::map< std::string, std::string > get_header_filters( void ) const;
                
                std::function< Response ( const Request& ) > get_method_handler( const Method& verb ) const;
            
                std::map< Method, std::function< Response ( const Request& ) > > get_method_handlers( void ) const;
                
                //Setters
                void set_path( const std::string& value );
            
                void set_paths( const std::vector< std::string >& values );
                
                void set_header_filter( const std::string& name, const std::string& value );
            
                void set_header_filters( const std::map< std::string, std::string >& values );
            
                void set_method_handler( const Method& verb, const std::function< Response ( const Request& ) >& callback );
            
                void set_method_handlers( const std::map< Method, std::function< Response ( const Request& ) > >& values );
            
                //Operators
                bool operator <( const ResourceImpl& value ) const;
                
                bool operator >( const ResourceImpl& value ) const;
                
                bool operator ==( const ResourceImpl& value ) const;
                
                bool operator !=( const ResourceImpl& value ) const;
                
                ResourceImpl& operator =( const ResourceImpl& value );
                
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
                void setup( void );
                
                std::string generate_allow_header_value( void );
                
                Response default_options_handler( const Request& request );
            
                Response default_method_not_allowed_handler( const Request& request );
            
                static std::string rebuild_path( const Request& request );
                
                static Response default_trace_handler( const Request& request );
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::vector< std::string > m_paths;
            
                std::vector< std::string > m_allow_methods;
            
                std::map< std::string, std::string > m_header_filters;
                
                std::map< std::string, std::function< Response ( const Request& ) > > m_method_handlers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_IMPL_H */
