/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _TEST_LOGGER_H
#define _TEST_LOGGER_H 1

//System Includes
#include <string>
#include <vector>
#include <cstdarg>

//Project Includes
#include <restbed>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

class TestLogger : public restbed::Logger
{
    public:
        //Friends
        
        //Definitions
        
        //Constructors
        TestLogger( void );
        
        virtual ~TestLogger( void );
        
        //Functionality
        void log( const restbed::LogLevel level, const std::string format, ... ) noexcept;
        
        //Getters
        const char* get_log_entry( void ) const;
        
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
        TestLogger( const TestLogger& original ) = delete;
        
        //Functionality
        
        //Getters
        
        //Setters
        
        //Operators
        TestLogger& operator =( const TestLogger& rhs ) = delete;
        
        //Properties
        std::vector< std::string > m_log_entries;
};

#endif  /* _TEST_LOGGER_H */
