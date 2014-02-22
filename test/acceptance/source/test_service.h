/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include <restbed>
#include "test_logger.h"

//External Includes

//System Namespaces
using std::string;
using std::vector;

//Project Namespaces
using restbed::Service;
using restbed::Request;
using restbed::Response;
using restbed::Settings;
using restbed::LogLevel;

//External Namespaces

class TestService : public Service
{
	public:
		TestService( const Settings& settings ) : Service( settings ),
												  m_logger( )
		{
			set_logger( m_logger );
		}

		const char* get_log_entry( void ) const
		{
			return m_logger.get_log_entry( );
		}

	private:
		TestLogger m_logger;
};
