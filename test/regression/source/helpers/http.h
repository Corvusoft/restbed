/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <map>
#include <cstdio>
#include <string>

//Project Includes

//External Includes
#include <curl/curl.h>

//System Namespaces
using std::map;
using std::string;
using std::to_string;

//Project Namespaces

//External Namespaces

#include <iostream>
using namespace std;

class Http
{
	public:
		static map< string, string > get( const string& url )
		{
			return get( url, map< string, string >( ) );
		}

		static map< string, string > get( const string& url, map< string, string > headers )
		{
			map< string, string > result;

			curl_slist* hdrs = nullptr;

			for ( auto header : headers )
			{
				string value = header.first + ": " + header.second;

				hdrs = curl_slist_append( hdrs, value.data( ) );
			}
    		
    		CURL* request = curl_easy_init( );
			curl_easy_setopt( request, CURLOPT_URL, url.data( ) );
    		curl_easy_setopt( request, CURLOPT_WRITEDATA, fopen( "/dev/null", "wb" ) );
       		curl_easy_setopt( request, CURLOPT_HTTPHEADER, hdrs );

			CURLcode response = curl_easy_perform( request );

			if ( response == CURLE_OK )
			{
				int status_code = 0;
				curl_easy_getinfo( request, CURLINFO_RESPONSE_CODE, &status_code );
				result[ "Status Code" ] = ::to_string( status_code );
			}

			curl_easy_cleanup( request );

			return result;
		}

	private:
		Http( void ) = delete;
		~Http( void ) = delete;
		Http& operator =( const Http& ) = delete;
};
