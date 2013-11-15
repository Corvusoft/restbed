/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_HELPER_ISTREAM_H
#define _RESTBED_DETAIL_HELPER_ISTREAM_H 1

//System Includes
#include <istream>

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
            
            class IStream
            {
                public:
                    //Friends
                    
                    //Definitions

                    //Constructors
                    
                    //Functionality
			        static char reverse_peek( std::istream& socket );

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
                    IStream( void ) = delete;
                    
                    IStream( const IStream& original ) = delete;
                    
                    virtual ~IStream( void ) = delete;

                    //Functionality
                    
                    //Getters
                    
                    //Setters
                    
                    //Operators
                    IStream& operator =( const IStream& rhs ) = delete;

                    //Properties
            };
        }
    }
}

#endif  /* _RESTBED_DETAIL_HELPER_ISTREAM_H */
