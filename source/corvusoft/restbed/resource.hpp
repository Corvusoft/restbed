/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <set>
#include <string>
#include <functional>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define RESOURCE_EXPORT __declspec(dllexport)
	#else
		#define RESOURCE_EXPORT __declspec(dllimport)
	#endif
#else
	#define RESOURCE_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Service;
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
        struct ResourceImpl;
    }
    
    class Resource
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            RESOURCE_EXPORT Resource( void );
            
            RESOURCE_EXPORT virtual ~Resource( void );
            
            //Functionality
            
            //Getters
            
            //Setters
            RESOURCE_EXPORT void set_path( const std::string& value );
            
            RESOURCE_EXPORT void set_paths( const std::set< std::string >& values );
            
            RESOURCE_EXPORT void set_default_header( const std::string& name, const std::string& value );
            
            RESOURCE_EXPORT void set_default_headers( const std::multimap< std::string, std::string >& values );
            
            RESOURCE_EXPORT void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) >& value );
            
            RESOURCE_EXPORT void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) >& value );
            
            RESOURCE_EXPORT void set_method_handler( const std::string& method, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
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
            friend Service;
            friend detail::ServiceImpl;
            friend detail::SessionImpl;
            
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
