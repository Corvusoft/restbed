/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::bind;
using std::shared_ptr;
using std::make_shared;
using std::placeholders::_1;

//Project Namespaces
using namespace restbed;

//External Namespaces
using testing::TestWithParam;

class ServiceFixture : public TestWithParam< int >
{
	public: 
		ServiceFixture( void ) : m_port( 1984 ),
				   			     m_service( nullptr )
		{
			//n/a
		}

		~ServiceFixture( void )
		{
			//n/a
		}

	protected:
		void SetUp( void )
		{
		    Resource resource;
		    resource.set_method_handler( "GET", bind( &ServiceFixture::get_handler, this, _1 ) );

		    Settings settings;
		    settings.set_port( m_port );
		    settings.set_root( "test" );
		    settings.set_mode( ASYNCHRONOUS );

		    m_service = make_shared< Service >( settings );
		    m_service->publish( resource );

		    m_service->start( );
		}

		void TearDown( void )
		{
			m_service->stop( );
		}

	private:
		Response get_handler( const Request& )
		{
		    Response response;
		    response.set_status_code( StatusCode::OK );

		    return response;
		}

		int m_port;

		std::shared_ptr< Service > m_service;
};
