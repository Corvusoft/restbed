/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SERVICE_H
#define _RESTBED_SERVICE_H 1

//System Includes
#include <map>
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
    class Rule;
    class Logger;
    class Session;
    class Resource;
    class Settings;
    class SSLSettings;
    
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
            void stop( void );
   
            void start( const std::shared_ptr< const Settings >& settings = nullptr );

            void restart( const std::shared_ptr< const Settings >& settings = nullptr );

            void add_rule( const std::shared_ptr< const Rule >& rule );

            void publish( const std::shared_ptr< const Resource >& resource );
            
            void suppress( const std::shared_ptr< const Resource >& resource );
            
            //Getters
            
            //Setters
            void set_logger( const std::shared_ptr< Logger >& value );

            void set_ready_handler( const std::function< void ( Service& ) >& value );
            
            void set_not_found_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );
            
            void set_method_not_allowed_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );
            
            void set_method_not_implemented_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );
            
            void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );
            
            void set_error_handler( std::function< void ( const int, const std::exception&, const std::shared_ptr< Session >& ) > value );

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
