/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <vector>
#include <utility>
#include <stdexcept>

//Project Includes
#include "corvusoft/restbed/detail/path_parameter_impl.h"

//External Includes
#include <corvusoft/framework/string>

//System Namespaces
using std::map;
using std::pair;
using std::string;
using std::vector;
using std::make_pair;
using std::invalid_argument;

//Project Namespaces
using framework::String;

//External Namespaces

namespace restbed
{
    namespace detail
    {
        string PathParameterImpl::parse( const string& declaration )
        {
            auto definition = parse_declaration( declaration );
            
            return definition.second;
        }
        
        map< string, string > PathParameterImpl::parse( const string& path, const string& declaration )
        {
            map< string, string > parameters;
            
            auto declarations = String::split( declaration, '/' );
            
            auto paths = String::split( path, '/' );
            
            for ( vector< string >::size_type index = 0; index not_eq declarations.size( ); index++ )
            {
                auto definition = parse_declaration( declarations[ index ] );
                
                if ( not definition.first.empty( ) and index < paths.size( ) )
                {
                    parameters[ definition.first ] = paths[ index ];
                }
            }
            
            return parameters;
        }
        
        pair< string, string > PathParameterImpl::parse_declaration( const string& declaration )
        {
            string name = String::empty;
            string pattern = declaration;
            
            if ( declaration.front( ) == '{' and declaration.back( ) == '}' )
            {
                string definition = String::trim( declaration, "{" );
                definition = String::trim( definition, "}" );
                
                auto segments = String::split( definition, ':' );
                
                if ( segments.size( ) not_eq 2 )
                {
                    throw invalid_argument( String::empty );
                }
                
                name = String::trim( segments[ 0 ] );
                pattern = String::trim( segments[ 1 ] );
            }
            
            return make_pair( name, pattern );
        }
    }
}
