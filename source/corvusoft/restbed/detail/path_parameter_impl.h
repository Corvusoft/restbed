/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_PATH_PARAMETER_IMPL_H
#define _RESTBED_DETAIL_PATH_PARAMETER_IMPL_H 1

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
        
        class PathParameterImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                static std::string parse( const std::string& declaration );
                
                static std::map< std::string, std::string > parse( const std::string& path, const std::string& declaration );
                
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
                PathParameterImpl( void ) = delete;
                
                PathParameterImpl( const PathParameterImpl& original ) = delete;
                
                virtual ~PathParameterImpl( void ) = delete;
                
                //Functionality
                static std::pair< std::string, std::string > parse_declaration( const std::string& declaration );
                
                //Getters
                
                //Setters
                
                //Operators
                PathParameterImpl& operator =( const PathParameterImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_PATH_PARAMETER_IMPL_H */
