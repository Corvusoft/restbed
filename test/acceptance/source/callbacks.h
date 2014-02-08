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
using restbed::Request;
using restbed::Response;

//External Namespaces

Response ok_callback_handler( const Request&, const string& header, const string& value )
{
	Response response;
	response.set_status_code( 200 );

	if ( header.length( ) )
	{
		response.set_header( header, value );
	}

	return response;
}

Response json_ok_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "{string:\'Hello World\'}" );

	return response;
}

Response xml_ok_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );
	response.set_body( "<response><string>Hello World</string></response>" );

	return response;
}
