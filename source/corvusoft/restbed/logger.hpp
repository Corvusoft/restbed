/*
 * Copyright 2013-2020, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

#if defined(_WIN32)
    #undef ERROR
#endif

//System Includes
#include <string>
#include <memory>

//Project Includes

//External Includes

//Windows DLL Exports
#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
	#ifdef WIN_DLL_EXPORT
		#define LOGGER_EXPORT __declspec(dllexport)
	#else
		#define LOGGER_EXPORT __declspec(dllimport)
	#endif
#else
	#define LOGGER_EXPORT __attribute__((visibility ("default")))
#endif

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Settings;
    
    class Logger
    {
        public:
            //Friends
            
            //Definitions
            enum Level : int
            {
                INFO = 0000,
                DEBUG = 1000,
                FATAL = 2000,
                ERROR = 3000,
                WARNING = 4000,
                SECURITY = 5000
            };
            
            //Constructors
            
            //Functionality
            LOGGER_EXPORT virtual void stop( void ) = 0;
            
            LOGGER_EXPORT virtual void start( const std::shared_ptr< const Settings >& settings ) = 0;
            
            LOGGER_EXPORT virtual void log( const Level level, const char* format, ... ) = 0;
            
            LOGGER_EXPORT virtual void log_if( bool expression, const Level level, const char* format, ... ) = 0;
            
            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            //Friends
            
            //Definitions
            
            //Constructors
            LOGGER_EXPORT Logger( void ) = default;
            
            LOGGER_EXPORT explicit Logger( const Logger& original ) = default;
            
            LOGGER_EXPORT virtual ~Logger( void ) = default;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            LOGGER_EXPORT Logger& operator =( const Logger& value ) = default;
            
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
    };
}
