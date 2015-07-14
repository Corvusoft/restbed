/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_MAP_IMPL_H
#define _RESTBED_DETAIL_MAP_IMPL_H 1

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
        
        class MapImpl
        {
            public:
                //Friends
                
                //Definitions
                typedef std::map< std::string, std::string >::iterator iterator;
                
                typedef std::map< std::string, std::string >::const_iterator const_iterator;
                
                //Constructors
                
                //Functionality
                static iterator find_ignoring_case( const std::string& key, std::map< std::string, std::string >& container );
                
                static const_iterator find_ignoring_case( const std::string& key, const std::map< std::string, std::string >& container );
                
                static iterator find_ignoring_case( const std::string& key, std::multimap< std::string, std::string >& container );
                
                static const_iterator find_ignoring_case( const std::string& key, const std::multimap< std::string, std::string >& container );
                
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
                MapImpl( void ) = delete;
                
                MapImpl( const MapImpl& original ) = delete;
                
                virtual ~MapImpl( void ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                MapImpl& operator =( const MapImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_MAP_IMPL_H */
