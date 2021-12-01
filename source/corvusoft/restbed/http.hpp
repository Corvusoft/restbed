/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <string>
#include <memory>
#include <future>
#include <cstddef>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define HTTP_EXPORT __declspec(dllexport)
	#else
		#define HTTP_EXPORT __declspec(dllimport)
	#endif
	#define DEPRECATED(MSG) __declspec(deprecated(MSG))
#else
    // gcc11 and clang12 don't like mixing __attribute__ and [[deprecated(MSG)]]
	#define HTTP_EXPORT __attribute__((visibility ("default")))
	#define DEPRECATED(MSG) __attribute__((__deprecated__(MSG)))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Response;
    class Settings;

    class DEPRECATED("HTTP client is deprecated; we will release a complimentary client framework at a future date.") HTTP_EXPORT Http
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            
            //Functionality
            static Bytes to_bytes( const std::shared_ptr< Request >& value );
            
            static Bytes to_bytes( const std::shared_ptr< Response >& value );
            
            static void close( const std::shared_ptr< Request >& value );
            
            static bool is_open( const std::shared_ptr< Request >& value );
            
            static bool is_closed( const std::shared_ptr< Request >& value );
            
            static const std::shared_ptr< Response > sync( const std::shared_ptr< Request > request, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
            
            static std::future< std::shared_ptr< Response > > async( const std::shared_ptr< Request > request, const std::function< void ( const std::shared_ptr< Request >, const std::shared_ptr< Response > ) >& callback, const std::shared_ptr< const Settings >& settings = std::make_shared< Settings >( ) );
            
            static Bytes fetch( const std::size_t length, const std::shared_ptr< Response >& response );
            
            static Bytes fetch( const std::string& delimiter, const std::shared_ptr< Response >& response );
            
            //Getters
            
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
            
            //Definitions
            
            //Constructors
            Http( void ) = delete;
            
            virtual ~Http( void ) = delete;
            
            Http( const Http& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Http& operator =( const Http& value ) = delete;
            
            //Properties
    };
}
