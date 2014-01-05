/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include <restbed>

//External Includes

//System Namespaces

//Project Namespaces
using restbed::Request;
using restbed::Response;

//External Namespaces

Response callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );

	return response;
}

Response json_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "{string:\'Hello World\'}" );

	return response;
}

Response xml_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "<response><string>Hello World</string></response>" );

	return response;
}

Response api_1_0_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "api version 1.0" );

	return response;
}

Response api_1_1_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "api version 1.1" );

	return response;
}