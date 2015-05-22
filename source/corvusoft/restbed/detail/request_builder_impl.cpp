/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes
#include <regex>
#include <string>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/detail/request_impl.h"
#include "corvusoft/restbed/detail/request_builder_impl.h"

//External Includes
#include <corvusoft/framework/uri>
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::regex;
using std::smatch;
using std::string;
using std::istream;
using std::multimap;
using std::shared_ptr;
using std::make_shared;
using std::runtime_error;

//Project Namespaces

//External Namespaces
using framework::Uri;
using framework::String;

namespace restbed
{
    namespace detail
    {
        RequestBuilderImpl::RequestBuilderImpl( istream& stream ) : Request( )
        {
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );

            auto request = make_shared< Request >( );
            m_pimpl->set_path( uri.get_path( ) );
            m_pimpl->set_method( items.at( "method" ) );
            m_pimpl->set_version( stod( items.at( "version" ) ) );
            m_pimpl->set_headers( parse_request_headers( stream ) );
            //request->m_pimpl->set_query_parameters( uri.get_query_parameters( ) );
        }
        
        RequestBuilderImpl::~RequestBuilderImpl( void )
        {
            return;
        }

        const map< string, string > RequestBuilderImpl::parse_request_line( istream& stream )
        {
            smatch matches;
            static const regex pattern( "^(.*) (.*) (HTTP\\/[0-9]\\.[0-9])\\s*$" );
            string data = String::empty;
            getline( stream, data );

            if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 4 )
            {
                throw runtime_error( "FAILED BAD REQUEST!" );
            }

            const string protocol = matches[ 3 ].str( );
            const auto delimiter = protocol.find_first_of( "HTTP/" );

            return map< string, string > {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", protocol.substr( delimiter ) },
                { "protocol", protocol.substr( 0, delimiter ) },
            };
        }

        const multimap< string, string > RequestBuilderImpl::parse_request_headers( istream& stream )
        {
            smatch matches;
            string data = String::empty;
            multimap< string, string > headers;
            static const regex pattern( "^(.*): *(.*)\\s*$" );

            while ( getline( stream, data ) and data not_eq "\r" )
            {
                if ( not regex_match( data, matches, pattern ) or matches.size( ) not_eq 3 )
                {
                    throw runtime_error( "FAILED BAD REQUEST!" );
                }

                headers.insert( make_pair( matches[ 1 ].str( ), matches[ 2 ].str( ) ) );
            }

            return headers;
        }
    }
}
