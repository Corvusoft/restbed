/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_PATH_PARAMETER_H
#define _RESTBED_DETAIL_PATH_PARAMETER_H 1

//System Includes
#include <map>
#include <regex>
#include <string>
#include <utility>

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
        
        class PathParameter
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                
                //Functionality
                static std::regex parse( const std::string& declaration );

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
                PathParameter( void ) = delete;
                
                PathParameter( const PathParameter& original ) = delete;
                
                virtual ~PathParameter( void ) = delete;

                //Functionality
                static std::pair< std::string, std::string > parse_declaration( const std::string& declaration );

                //Getters
                
                //Setters

                //Operators
                PathParameter& operator =( const PathParameter& rhs ) = delete;

                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_PATH_PARAMETER_H */
