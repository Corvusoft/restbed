/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SESSION_H
#define _RESTBED_SESSION_H 1

//System Includes
#include <string>
#include <memory>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Session;
    class Resource;
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
    }
    
    class Session
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Session( const std::string& id );

            virtual ~Session( void );
            
            //Functionality
            bool is_open( void ) const;

            bool is_closed( void ) const;

            void close( void );

            void close( const int status, const std::string& status_message = "" );

            void fetch( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            //Getters
            const std::string& get_id( void ) const;

            const std::shared_ptr< const Request > get_request(  void ) const;

            const std::shared_ptr< const Resource > get_resource( void ) const;

            //Setters
            
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
            friend detail::ServiceImpl;
            friend detail::SessionImpl;

            //Definitions
            
            //Constructors
            Session( void ) = delete;

            Session( const Session& original ) = delete;
            
            //Functionality

            //Getters
            
            //Setters
            
            //Operators
            Session& operator =( const Session& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::SessionImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SESSION_H */
