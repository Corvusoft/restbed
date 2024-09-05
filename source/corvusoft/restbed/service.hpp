/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <chrono>
#include <memory>
#include <string>
#include <stdexcept>
#include <functional>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define SERVICE_EXPORT __declspec(dllexport)
	#else
		#define SERVICE_EXPORT __declspec(dllimport)
	#endif
#else
	#define SERVICE_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Rule;
    class Logger;
    class Session;
    class Resource;
    class Settings;
    class SessionManager;
    
    namespace detail
    {
        class ServiceImpl;
    }
    
    class Service
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            SERVICE_EXPORT Service( void );
            
            SERVICE_EXPORT virtual ~Service( void );
            
            //Functionality
            SERVICE_EXPORT bool is_up( void ) const;
            
            SERVICE_EXPORT bool is_down( void ) const;
            
            SERVICE_EXPORT void stop( void );
            
            SERVICE_EXPORT void start( const std::shared_ptr< const Settings >& settings = nullptr );
            
            SERVICE_EXPORT void restart( const std::shared_ptr< const Settings >& settings = nullptr );
            
            SERVICE_EXPORT void add_rule( const std::shared_ptr< Rule >& rule );
            
            SERVICE_EXPORT void add_rule( const std::shared_ptr< Rule >& rule, const int priority );
            
            SERVICE_EXPORT void publish( const std::shared_ptr< const Resource >& resource );
            
            SERVICE_EXPORT void suppress( const std::shared_ptr< const Resource >& resource );
            
            SERVICE_EXPORT void schedule( const std::function< void ( void ) >& task, const std::chrono::milliseconds& interval = std::chrono::milliseconds::zero( ) );
            
            //Getters
            SERVICE_EXPORT const std::chrono::seconds get_uptime( void ) const;
            
            SERVICE_EXPORT const std::shared_ptr< const Uri > get_http_uri( void ) const;
            
            SERVICE_EXPORT const std::shared_ptr< const Uri > get_https_uri( void ) const;
            
            //Setters
            SERVICE_EXPORT void set_logger( const std::shared_ptr< Logger >& value );
            
            SERVICE_EXPORT void set_session_manager( const std::shared_ptr< SessionManager >& value );
            
            SERVICE_EXPORT void set_ready_handler( const std::function< void ( Service& ) >& value );
            
            SERVICE_EXPORT void set_signal_handler( const int signal, const std::function< void ( const int ) >& value );
            
            SERVICE_EXPORT void set_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            SERVICE_EXPORT void set_method_not_allowed_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            SERVICE_EXPORT void set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            SERVICE_EXPORT void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            SERVICE_EXPORT void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) >& value );
            
            SERVICE_EXPORT void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) >& value );
            
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
            Service( const Service& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Service& operator =( const Service& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::ServiceImpl > m_pimpl;
    };
}
