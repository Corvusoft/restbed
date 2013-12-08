/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_HELPERS_DATE_H
#define _RESTBED_DETAIL_HELPERS_DATE_H 1

//System Includes
#include <string>
#include <chrono>

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

            class Date
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
                    static std::string format( const std::chrono::time_point< std::chrono::system_clock >& value );

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
                    Date( void ) = delete;
                    
                    Date( const Date& original ) = delete;
                    
                    virtual ~Date( void ) = delete;

                    //Functionality
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    Date& operator =( const Date& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPERS_DATE_H */
