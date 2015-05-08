/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_RESOURCE_H
#define _RESTBED_RESOURCE_H 1

//System Includes
#include <map>
#include <set>
#include <memory>
#include <string>
#include <utility>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/string>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
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
            
            virtual ~Resource( void );
            
            //Functionality
            
            //Getters
            std::string get_id( void ) const;

            std::set< std::string > get_paths( void ) const;

            std::multimap< std::string, std::pair< std::multimap< std::string, std::string >, std::function< Response ( const Request& ) > > >
            get_method_handlers( const std::string& method = framework::String::empty ) const;

            //Setters
            void set_paths( const std::set< std::string >& values );

            void set_method_handler( const std::string& method,
                                     const std::function< Response ( const Request& ) >& callback );

            void set_method_handler( const std::string& method,
                                     const std::multimap< std::string, std::string >& filters,
                                     const std::function< Response ( const Request& ) >& callback );

            void set_authentication_handler( const std::function< void ( const Request&, Response& ) >& value );
                
            void set_error_handler( const std::function< void ( const int, const Request&, Response& ) >& value );
            
            //Operators
            Resource& operator =( const Resource& value );

            bool operator >( const Resource& value ) const;

            bool operator <( const Resource& value ) const;

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
