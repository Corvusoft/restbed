/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_LOGGER_IMPL_H
#define _RESTBED_DETAIL_LOGGER_IMPL_H 1

//System Includes
#include <memory>
#include <string>
#include <cstdarg>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    enum LogLevel :
    int;
    
    namespace detail
    {
        //Forward Declarations
        
        class LoggerImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                LoggerImpl( void );
                
                LoggerImpl( const LoggerImpl& original );
                
                virtual ~LoggerImpl( void );
                
                //Functionality
                void log( const LogLevel level, const std::string format, va_list arguments ) const;
                
                void log_if( bool expression, const LogLevel level, const std::string format, va_list arguments ) const;
                
                //Getters
                
                //Setters
                
                //Operators
                LoggerImpl& operator =( const LoggerImpl& value );
                
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
                std::string build_log_label( const LogLevel level ) const;
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_LOGGER_IMPL_H */
