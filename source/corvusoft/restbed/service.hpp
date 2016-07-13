/*
 * Copyright 2013-2016, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_SERVICE_H
#define _RESTBED_SERVICE_H 1

//System Includes
#include <map>
#include <chrono>
#include <memory>
#include <string>
#include <stdexcept>
#include <functional>

//Project Includes

//External Includes

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
            Service( void );
            
            virtual ~Service( void );
            
            //Functionality
            bool is_up( void ) const;
            
            bool is_down( void ) const;
            
            void stop( void );
            
            void start( const std::shared_ptr< const Settings >& settings = nullptr );
            
            void restart( const std::shared_ptr< const Settings >& settings = nullptr );
            
            void add_rule( const std::shared_ptr< Rule >& rule );
            
            void add_rule( const std::shared_ptr< Rule >& rule, const int priority );
            
            void publish( const std::shared_ptr< const Resource >& resource );
            
            void suppress( const std::shared_ptr< const Resource >& resource );
            
            void schedule( const std::function< void ( void ) >& task, const std::chrono::milliseconds& interval = std::chrono::milliseconds::zero( ) );
            
            //Getters
            const std::chrono::seconds get_uptime( void ) const;
            
            const std::shared_ptr< const Uri > get_http_uri( void ) const;
            
            const std::shared_ptr< const Uri > get_https_uri( void ) const;
            
            //Setters
            void set_logger( const std::shared_ptr< Logger >& value );
            
            void set_session_manager( const std::shared_ptr< SessionManager >& value );
            
            void set_ready_handler( const std::function< void ( Service& ) >& value );
            
            void set_signal_handler( const int signal, const std::function< void ( const int ) >& value );
            
            void set_not_found_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            void set_method_not_allowed_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            void set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session > ) >& value );
            
            void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session > ) >& value );
            
            void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >, const std::function< void ( const std::shared_ptr< Session > ) >& ) >& value );
            
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

#endif  /* _RESTBED_SERVICE_H */
