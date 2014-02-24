/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _TEST_SERVICE_H
#define _TEST_SERVICE_H 1

//System Includes
#include <memory>

//Project Includes
#include <restbed>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

class TestService : public restbed::Service
{
	public:
	    //Friends
	    
	    //Definitions

	    //Constructors
	    TestService( const restbed::Settings& settings );
	    
	    virtual ~TestService( void );

	    //Functionality
	    void suppress_resource( void );

		void publish_resource( restbed::Resource& resource );

	    //Getters
		const char* get_log_entry( void ) const;

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
	    TestService( const TestService& original ) = delete;

	    //Functionality
	    
	    //Getters
	    
	    //Setters
	    
	    //Operators
	    TestService& operator =( const TestService& rhs ) = delete;

	    //Properties
	 	restbed::Resource m_resource;
	 	
	 	std::shared_ptr< class TestLogger > m_logger;
};

#endif  /* _TEST_SERVICE_H */
