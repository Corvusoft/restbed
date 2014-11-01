/*
 * Copyright (c) 2013, 2014 Corvusoft
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
    class Request;
    class Response;
    class Resource;
    class Settings;
    
    enum Mode : int;

    enum LogLevel :
    int;
    
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
            
            Service( const Service& original );
        
            Service( const detail::ServiceImpl& implementation );
            
            virtual ~Service( void );
            
            //Functionality
            void start( void );
        
            void start( const Mode& value );
            
            void stop( void );
            
            void publish( const Resource& value );
            
            void suppress( const Resource& value );
            
            //Getters
            
            //Setters
            void set_logger( const std::shared_ptr< Logger >& value );
            
            void set_authentication_handler( std::function< void ( const Request&, Response& ) > value );
            
            void set_error_handler( std::function< void ( const int, const Request&, Response& ) > value );
            
            //Operators
            Service& operator =( const Service& value );
            
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
            std::unique_ptr< detail::ServiceImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SERVICE_H */
