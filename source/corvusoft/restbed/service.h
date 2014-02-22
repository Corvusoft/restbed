/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_SERVICE_H
#define _RESTBED_SERVICE_H 1

//System Includes
#include <memory>
#include <string>
 
//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Response;
    class Resource;
    class Settings;

    enum LogLevel : int;

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

            virtual ~Service( void );

            //Functionality
            void start( void );

            void stop( void );

            void publish( const Resource& value );

            void suppress( const Resource& value );

            //Getters

            //Setters
            void set_logger( Logger& value );

            //Operators
            Service& operator =( const Service& rhs );

            bool operator <( const Service& rhs ) const;
            
            bool operator >( const Service& rhs ) const;
            
            bool operator ==( const Service& rhs ) const;
            
            bool operator !=( const Service& rhs ) const;

            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            virtual void error_handler( const Request& request, /*out*/ Response& response );

            virtual void authentication_handler( const Request& request, /*out*/ Response& response );

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
