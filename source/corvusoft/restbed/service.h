/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SERVICE_H
#define _RESTBED_SERVICE_H 1

//System Includes
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
    class Logger;
    class Session;
    class Resource;
    class Settings;
    
    enum Mode : int;
    
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
            Service( const Settings& settings );
        
            virtual ~Service( void );
            
            //Functionality
            void stop( void );

            void start( void );
            
            void publish( const std::shared_ptr< Resource >& value );
            
            void suppress( const std::shared_ptr< Resource >& value );
            
            //Getters
            
            //Setters
            void set_logger( const std::shared_ptr< Logger >& value );
            
            void set_authentication_handler( std::function< void ( const std::shared_ptr< Session >& ) > value );
            
            void set_error_handler( std::function< void ( const int, const std::shared_ptr< Session >& ) > value );
            
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
