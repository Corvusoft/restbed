/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SESSION_H
#define _RESTBED_SESSION_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/bytes>
#include <corvusoft/framework/string>

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

            void close( const int status, const std::string& body = framework::String::empty );

            void close( const int status, const std::multimap< std::string, std::string >& headers );

            void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

            void yield( const int status, const std::string& body = framework::String::empty );

            void yield( const int status, const std::multimap< std::string, std::string >& headers );

            void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

            void fetch( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void fetch( const std::size_t length,
                        const std::function< void ( const std::shared_ptr< Session >&, const std::shared_ptr< framework::Bytes >& ) >& callback );

            void fetch( const std::string& delimiter,
                        const std::function< void ( const std::shared_ptr< Session >&, const std::shared_ptr< framework::Bytes >& ) >& callback );

            //Getters
            const std::string& get_id( void ) const;

            const std::shared_ptr< const Request > get_request(  void ) const;

            const std::shared_ptr< const Resource > get_resource( void ) const;

            //Setters
        //set_default_header
        //set_deafult_headers
            
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
