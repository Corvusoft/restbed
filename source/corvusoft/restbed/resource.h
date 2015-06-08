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
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
        class ResourceImpl;
    }
    
    class Resource
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Resource( void );
            
            virtual ~Resource( void );
            
            //Functionality
            
            //Getters

            //Setters
            void set_path( const std::string& value );

            void set_paths( const std::set< std::string >& values );

            void set_default_header( const std::string& name, const std::string& value );

            void set_default_headers( const std::multimap< std::string, std::string >& values );

            void set_error_handler( const std::function< void ( const int, const std::shared_ptr< Session >& ) >& value );

            void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );

            void set_method_handler( const std::string& method, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void set_method_handler( const std::string& method, const std::multimap< std::string, std::string >& filters, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >&, const std::function< void ( const std::shared_ptr< Session >& ) >& ) >& value );
            
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
            friend detail::SessionImpl;
            friend detail::ServiceImpl;
            
            //Definitions
            
            //Constructors
            Resource( const Resource& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Resource& operator =( const Resource& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::ResourceImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_RESOURCE_H */
