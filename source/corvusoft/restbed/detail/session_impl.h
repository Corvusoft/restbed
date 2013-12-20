/*
 * Copyright (c) 2013 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SESSION_IMPL_H
#define _RESTBED_DETAIL_SESSION_IMPL_H 1

//System Includes
 
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
        
        class SessionImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                SessionImpl( void );
                
                SessionImpl( const SessionImpl& original );

                virtual ~SessionImpl( void );
                
                //Functionality

                //Getters
                
                //Setters

                //Operators
                bool operator <( const SessionImpl& rhs ) const;
                
                bool operator >( const SessionImpl& rhs ) const;
                
                bool operator ==( const SessionImpl& rhs ) const;
                
                bool operator !=( const SessionImpl& rhs ) const;

                SessionImpl& operator =( const SessionImpl& rhs );

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
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_IMPL_H */
