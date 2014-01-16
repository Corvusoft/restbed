/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _RESTBED_DETAIL_HELPERS_URI_H
#define _RESTBED_DETAIL_HELPERS_URI_H 1

//System Includes
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

        namespace helpers
        {
            //Forward Declarations

            class Uri
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
                    static std::string decode( const std::string& value );

                    static std::string decode_parameter( const std::string& value );

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
                    Uri( void ) = delete;
                    
                    Uri( const Uri& original ) = delete;
                    
                    virtual ~Uri( void ) = delete;

                    //Functionality

                    //Getters
                    
                    //Setters
                    
                    //Operators
                    Uri& operator =( const Uri& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPERS_URI_H */
