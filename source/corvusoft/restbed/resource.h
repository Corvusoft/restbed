/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_RESOURCE_H
#define _RESTBED_RESOURCE_H 1

//System Includes
#include <map>
#include <memory>
#include <vector>
#include <string>
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
        class ResourceImpl;
    }
    
    class Resource
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Resource( void );
            
            Resource( const Resource& original );
        
            Resource( const detail::ResourceImpl& implementation );
            
            virtual ~Resource( void );
            
            //Functionality
            
            //Getters
            std::string get_path( void ) const;
        
            std::vector< std::string > get_paths( void ) const;
        
            std::string get_header_filter( const std::string& name ) const;
            
            std::map< std::string, std::string > get_header_filters( void ) const;
            
            std::function< Response ( const Request& ) > get_method_handler( const Method& method ) const;
        
            std::map< Method, std::function< Response ( const Request& ) > > get_method_handlers( void ) const;
        
            //Setters
            void set_path( const std::string& value );
        
            void set_paths( const std::vector< std::string >& values );
            
            void set_header_filter( const std::string& name, const std::string& value );
        
            void set_header_filters( const std::map< std::string, std::string >& values );
        
            void set_method_handler( const Method& verb, const std::function< Response ( const Request& ) >& callback );
        
            void set_method_handlers( const std::map< Method, std::function< Response ( const Request& ) > >& values );
        
            //Operators
            Resource& operator =( const Resource& value );
        
            bool operator <( const Resource& value ) const;
            
            bool operator >( const Resource& value ) const;
            
            bool operator ==( const Resource& value ) const;
            
            bool operator !=( const Resource& value ) const;
            
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
            std::unique_ptr< detail::ResourceImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_RESOURCE_H */
