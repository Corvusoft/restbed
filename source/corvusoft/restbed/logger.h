/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_LOGGER_H
#define _RESTBED_LOGGER_H 1

//System Includes
#include <string>
#include <memory>

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
        class LoggerImpl;
    }
    
    class Logger
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Logger( void );
            
            Logger( const Logger& original );
            
            virtual ~Logger( void );
            
            //Functionality
            virtual void log( const LogLevel level, const std::string format, ... ) noexcept;
            
            virtual void log_if( bool expression, const LogLevel level, const std::string format, ... ) noexcept;
            
            //Getters
            
            //Setters
            
            //Operators
            Logger& operator =( const Logger& rhs );
            
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
            const std::unique_ptr< detail::LoggerImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_LOGGER_H */
