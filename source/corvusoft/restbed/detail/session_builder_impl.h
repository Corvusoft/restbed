/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SESSION_BUILDER_IMPL_H
#define _RESTBED_DETAIL_SESSION_BUILDER_IMPL_H 1

//System Includes
#include <memory>

//Project Includes
#include "corvusoft/restbed/session.h"

//External Includes
#include <asio.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        //Forward Declarations
        
        class SessionBuilderImpl : public Session
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionBuilderImpl( const std::string& id );
                
                virtual ~SessionBuilderImpl( void );
                
                //Functionality
                void set_request( const std::shared_ptr< Request >& value );

                void set_socket( const std::shared_ptr< asio::ip::tcp::socket >& value );
                
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
                SessionBuilderImpl( void ) = delete;

                SessionBuilderImpl( const SessionBuilderImpl& original ) = delete;
                
                //Functionality

                //Getters
                
                //Setters
                
                //Operators
                SessionBuilderImpl& operator =( const SessionBuilderImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_BUILDER_IMPL_H */
