/*
 * Copyright 2013-2025, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <vector>
#include <cstdarg>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define STRING_EXPORT __declspec(dllexport)
	#else
		#define STRING_EXPORT __declspec(dllimport)
	#endif
#else
	#define STRING_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    class String
    {
        public:
            //Friends
            
            //Definitions
            enum Option : int
            {
                CASE_SENSITIVE = 0,
                CASE_INSENSITIVE = 1
            };
            
            //Constructors
            
            //Functionality
            STRING_EXPORT static Bytes to_bytes( const std::string& value );
            
            STRING_EXPORT static std::string lowercase( const std::string& value );
            
            STRING_EXPORT static std::string uppercase( const std::string& value );
            
            STRING_EXPORT static std::string format( const char* format, ... );
            
            STRING_EXPORT static std::vector< std::string > split( const std::string& text, const char delimiter );
            
            STRING_EXPORT static std::string join( const std::multimap< std::string, std::string >& values, const std::string& pair_delimiter, const std::string& delimiter );
            
            STRING_EXPORT static std::string remove( const std::string& needle, const std::string& haystack, const Option option = CASE_SENSITIVE );
            
            STRING_EXPORT static std::string replace( const std::string& target, const std::string& substitute, const std::string& value, const Option option = CASE_SENSITIVE );
            
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
            String( void ) = delete;
            
            String( const String& original ) = delete;
            
            virtual ~String( void ) = delete;
            
            //Functionality
            static std::string::size_type format( std::string& output, const std::string::size_type length, const char* format, va_list arguments );
            
            //Getters
            
            //Setters
            
            //Operators
            String& operator =( const String& value ) = delete;
            
            //Properties
    };
}
