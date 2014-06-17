/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_STATUS_CODE_IMPL_H
#define _RESTBED_DETAIL_STATUS_CODE_IMPL_H 1

//System Includes
#include <map>
#include <string>

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
        
        class StatusCodeImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                static int parse( const std::string& value );
                
                static std::string to_string( const int code );
                
                //Getters
                static std::map< int, std::string > get_mappings( void );
                
                //Setters
                static void set_mappings( const std::map< int, std::string >& values );
                
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
                StatusCodeImpl( void ) = delete;
                
                StatusCodeImpl( const StatusCodeImpl& original ) = delete;
                
                virtual ~StatusCodeImpl( void ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                StatusCodeImpl& operator =( const StatusCodeImpl& value ) = delete;
                
                //Properties
                static std::map< int, std::string > m_mappings;
        };
    }
}

#endif  /* _RESTBED_DETAIL_STATUS_CODE_IMPL_H */
