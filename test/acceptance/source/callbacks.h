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

Response ok_callback_handler( const Request& )
{
	Response response;
	response.set_status_code( 200 );

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

Response resource_with_response_header_handler( const Request&, const string& name, const string& value )
{
	Response response;
	response.set_status_code( 200 );
	response.set_header( name, value );

	return response;
}