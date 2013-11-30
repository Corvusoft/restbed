/*
 * Copyright (c) 2013 Corvusoft
 */

#ifdef __APPLE__
#define GTEST_USE_OWN_TR1_TUPLE 1 //See issue tracker #11
#endif

//System Includes
#include <chrono>
#include <thread>
#include <memory>
#include <functional>

//Project Includes
#include <restbed>

//External Includes
#include <gtest/gtest.h>

//System Namespaces
using std::bind;
using std::thread;
using std::shared_ptr;
using std::placeholders::_1;
using std::chrono::milliseconds;

//Project Namespaces
using namespace restbed;

//External Namespaces
using testing::TestWithParam;

class ServiceFixture : public TestWithParam< int >
{
	public: 
		ServiceFixture( void ) : m_port( 1984 ),
				   			     m_service( nullptr ),
								 m_service_thread( nullptr )
		{
			//n/a
		}

		~ServiceFixture( void )
		{
			delete m_service;
			delete m_service_thread;
		}

	protected:
		void SetUp( void )
		{
		    Resource resource;
		    resource.set_method_handler( "GET", bind( &ServiceFixture::get_handler, this, _1 ) );

		    Settings settings;
		    settings.set_port( m_port );
		    settings.set_root( "test" );

		    m_service = new Service( settings );
		    m_service->publish( resource );

		    m_service_thread = new thread( &Service::start, m_service );

		    std::this_thread::sleep_for( milliseconds( 1000 ) );
		}

		void TearDown( void )
		{
			m_service->stop( );
			m_service_thread->join( );
		}

	private:
		Response get_handler( const Request& )
		{
		    Response response;
		    response.set_status_code( StatusCode::OK );

		    return response;
		}

		int m_port;

		Service* m_service;

		thread* m_service_thread;
};
