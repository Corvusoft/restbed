/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_SESSION_H
#define _RESTBED_SESSION_H 1

//System Includes
#include <map>
#include <set>
#include <chrono>
#include <string>
#include <memory>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/string.hpp>
#include <corvusoft/restbed/context_value.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Session;
    class Response;
    class Resource;
    class WebSocket;
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
        class WebSocketManagerImpl;
    }
    
    class Session : public std::enable_shared_from_this< Session >
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            explicit Session( const std::string& id );
            
            virtual ~Session( void );
            
            //Functionality
            bool has( const std::string& name ) const;
            
            void erase( const std::string& name = "" );
            
            const std::set< std::string > keys( void ) const;
            
            bool is_open( void ) const;
            
            bool is_closed( void ) const;
            
            void close( const Bytes& body );
            
            void close( const Response& response );
            
            void close( const std::string& body = "" );
            
            void close( const int status, const Bytes& body );
            
            void close( const int status, const std::string& body = "" );
            
            void close( const int status, const std::multimap< std::string, std::string >& headers );
            
            void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );
            
            void close( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers );
            
            void yield( const Bytes& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const std::string& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const Response& response, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const int status, const Bytes& body = { }, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
            
            void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
            
            void upgrade( const int status, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void upgrade( const int status, const Bytes& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void upgrade( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void upgrade( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void upgrade( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void upgrade( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            void sleep_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            //Getters
            const std::string& get_id( void ) const;
            
            const std::string get_origin( void ) const;
            
            const std::string get_destination( void ) const;
            
            const std::shared_ptr< const Request > get_request(  void ) const;
            
            const std::shared_ptr< const Resource > get_resource( void ) const;
            
            const std::multimap< std::string, std::string >& get_headers( void ) const;
            
            const ContextValue& get( const std::string& name ) const;
            
            const ContextValue& get( const std::string& name, const ContextValue& default_value ) const;
            
            //Setters
            void set_id( const std::string& value );
            
            void set( const std::string& name, const ContextValue& value );
            
            void add_header( const std::string& name, const std::string& value );
            
            void set_header( const std::string& name, const std::string& value );
            
            void set_headers( const std::multimap< std::string, std::string >& values );
            
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
            friend detail::WebSocketManagerImpl;
            
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
