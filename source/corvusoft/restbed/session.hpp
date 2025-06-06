/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

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

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define SESSION_EXPORT __declspec(dllexport)
	#else
		#define SESSION_EXPORT __declspec(dllimport)
	#endif
#else
	#define SESSION_EXPORT __attribute__((visibility ("default")))
#endif

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
            SESSION_EXPORT Session( void );
            
            SESSION_EXPORT ~Session( void ) = default;
            
            //Functionality
            SESSION_EXPORT bool is_open( void ) const;
            
            SESSION_EXPORT bool is_closed( void ) const;
            
            SESSION_EXPORT void close( const Bytes& body );
            
            SESSION_EXPORT void close( const Response& response );
            
            SESSION_EXPORT void close( const std::string& body = "" );
            
            SESSION_EXPORT void close( const int status, const Bytes& body );
            
            SESSION_EXPORT void close( const int status, const std::string& body = "" );
            
            SESSION_EXPORT void close( const int status, const std::multimap< std::string, std::string >& headers );
            
            SESSION_EXPORT void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );
            
            SESSION_EXPORT void close( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers );
            
            SESSION_EXPORT void yield( const Bytes& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const std::string& data, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const Response& response, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const int status, const Bytes& body = { }, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session > ) >& callback = nullptr );
            
            SESSION_EXPORT void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
            
            SESSION_EXPORT void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session >, const Bytes& ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const Bytes& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void upgrade( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< WebSocket > ) >& callback );
            
            SESSION_EXPORT void sleep_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::shared_ptr< Session > ) >& callback );
            
            //Getters            
            SESSION_EXPORT const std::string get_origin( void ) const;
            
            SESSION_EXPORT const std::string get_destination( void ) const;
            
            SESSION_EXPORT const std::shared_ptr< const Request > get_request(  void ) const;
            
            SESSION_EXPORT const std::shared_ptr< const Resource > get_resource( void ) const;
            
            SESSION_EXPORT const std::multimap< std::string, std::string >& get_headers( void ) const;
            
            //Setters
            SESSION_EXPORT void add_header( const std::string& name, const std::string& value );
            
            SESSION_EXPORT void set_header( const std::string& name, const std::string& value );
            
            SESSION_EXPORT void set_headers( const std::multimap< std::string, std::string >& values );
            
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
            Session( const Session& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Session& operator =( const Session& value ) = delete;
            
            //Properties
            std::shared_ptr< detail::SessionImpl > m_pimpl;
    };
}
