/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_HELPERS_STRING_H
#define _RESTBED_DETAIL_HELPERS_STRING_H 1

//System Includes
#include <string>
#include <vector>
#include <cstdarg>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        namespace helpers
        {
            //Forward Declarations
            
            class String
            {
                public:
                    //Friends
                    
                    //Definitions
                    
                    //Constructors
                    
                    //Functionality
                    static std::string lowercase( const std::string& value );
                    
                    static std::string uppercase( const std::string& value );
                    
                    static std::string format( const std::string format, ... );
                    
                    static std::vector< std::string > split( const std::string& text, const char delimiter );
                    
                    static std::string trim( const std::string& value, const std::string& delimiter = " \t" );
                    
                    static std::string trim_leading( const std::string& value, const std::string& delimiter = " \t" );
                    
                    static std::string trim_lagging( const std::string& value, const std::string& delimiter = " \t" );
                    
                    static std::string remove( const std::string& needle, const std::string& haystack, bool case_insensitive = false );
                    
                    static std::string replace( const std::string& target, const std::string& substitute, const std::string& value, bool case_insensitive = false );
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    
                    //Properties
                    static const char* empty;
                    
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
                    static std::string::size_type format( /*out*/ std::string& output, const std::string::size_type length, const std::string format, va_list arguments );
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    String& operator =( const String& rhs ) = delete;
                    
                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPERS_STRING_H */
