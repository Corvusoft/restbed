/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_SESSION_H
#define _RESTBED_SESSION_H 1

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
        class SessionImpl;
    }
    
    class Session
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Session( void );
            
            Session( const Session& original );
        
            virtual ~Session( void );
            
            //Functionality            

            //Getters

            //Setters
            
            //Operators
            Session& operator =( const Session& value );
            
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
            std::unique_ptr< detail::SessionImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SESSION_H */
