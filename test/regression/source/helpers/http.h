/*
 * Copyright (c) 2013 Corvusoft
 */

//System Includes
#include <string>

//Project Includes

//External Includes
#include <curl/curl.h>

//System Namespaces
using std::string;

//Project Namespaces

//External Namespaces

class Http
{
	public:
		static int get( const string& url )
		{
			int status_code = 0;

			CURL* request = curl_easy_init( );

			curl_easy_setopt( request, CURLOPT_URL, url.data( ) );

			CURLcode response = curl_easy_perform( request );

			if ( response == CURLE_OK )
			{
				curl_easy_getinfo( request, CURLINFO_RESPONSE_CODE, &status_code );
			}

			curl_easy_cleanup( request );

			return status_code;
		}

	private:
		Http( void ) = delete;
		~Http( void ) = delete;
		Http& operator =( const Http& ) = delete;
};
