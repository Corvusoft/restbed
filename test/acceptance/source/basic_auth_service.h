/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _BASIC_AUTH_SERVICE_H
#define _BASIC_AUTH_SERVICE_H 1

//System Includes

//Project Includes
#include <restbed>
#include "test_service.h"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

class BasicAuthService : public TestService
{
	public:
	    //Friends
	    
	    //Definitions

	    //Constructors
	    BasicAuthService( const restbed::Settings& settings );
	    
	    virtual ~BasicAuthService( void );

	    //Functionality
	    virtual void authentication_handler( const restbed::Request& request, /*out*/ restbed::Response& response );

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
	    BasicAuthService( const BasicAuthService& original ) = delete;

	    //Functionality
	    
	    //Getters
	    
	    //Setters
	    
	    //Operators
	    BasicAuthService& operator =( const BasicAuthService& rhs ) = delete;

	    //Properties
};

#endif  /* _BASIC_AUTH_SERVICE_H */
