/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <string>

//Project Includes
#include <restbed>

//External Includes

//System Namespaces
using std::string;

//Project Namespaces
using restbed::Service;
using restbed::Request;
using restbed::Response;
using restbed::Settings;
using restbed::LogLevel;

//External Namespaces

class BasicAuthService : public Service
{
	public:
		BasicAuthService( const Settings& settings ) : Service( settings )
		{
			//n/a
		}

	protected:
		virtual void log_handler( const LogLevel, const std::string&, ... )
		{
			//n/a
		}

		virtual void authentication_handler( const Request& request, /*out*/ Response& response )
		{
			auto authorisation = request.get_header( "Authorization" );

			if ( authorisation == "Basic QWxhZGRpbjpvcGVuIHNlc2FtZQ==" )
			{
				response.set_status_code( 200 );
			}
			else
			{
				response.set_status_code( 401 );
				response.set_header( "WWW-Authenticate", "Basic realm=\"Restbed\"" );
			}
		}
};