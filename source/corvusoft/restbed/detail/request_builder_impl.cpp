/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/request.h"
#include "corvusoft/restbed/detail/request_builder_impl.h"

//External Includes

//System Namespaces
using std::map;
using std::istream;
using std::multimap;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        RequestBuilderImpl::RequestBuilderImpl( void ) : Request( )
        {
            return;
        }
        
        RequestBuilderImpl::RequestBuilderImpl( const RequestBuilderImpl& original ) : Request( original )
        {
            return;
        }
        
        RequestBuilderImpl::~RequestBuilderImpl( void )
        {
            return;
        }
        
        shared_ptr< Request > RequestBuilderImpl::build( istream& stream )
        {
            const auto items = parse_request_line( stream );
            const auto uri = Uri::parse( "http://localhost" + items.at( "path" ) );

            auto request = make_shared< Request >( );
            request->m_pimpl->set_path( uri.get_path( ) );
            request->m_pimpl->set_method( items.at( "method" ) );
            request->m_pimpl->set_version( stoi( items.at( "version" ) ) );
            request->m_pimpl->set_headers( parse_request_headers( stream ) );
            //request->m_pimpl->set_query_parameters( uri.get_query_parameters( ) );

            return request;
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

            const string version = matches[ 3 ].str( );

            return map< string, string > {
                { "path", matches[ 2 ].str( ) },
                { "method", matches[ 1 ].str( ) },
                { "version", version.substr( version.find_first_of( "HTTP/" ) ) }
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
