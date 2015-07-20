/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RULE_ENGINE_H
#define _RESTBED_DETAIL_RULE_ENGINE_H 1

//System Includes
#include <vector>
#include <memory>
#include <cstddef>

//Project Includes
#include "corvusoft/restbed/rule.hpp"
#include "corvusoft/restbed/session.hpp"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
	namespace detail
	{
        static void rule_engine( const std::shared_ptr< Session >& session,
                                 const vector< std::shared_ptr< Rule > >& rules,
                                 const std::function< void ( const std::shared_ptr< Session >& ) >& callback,
                                 std::size_t index = 0 )
        {
            while ( index not_eq rules.size( ) )
            {
                auto rule = rules.at( index );
                index++;

                if ( rule->condition( session ) )
                {
                    rule->action( session, bind( rule_engine, session, rules, callback, index ) );
                    return;
                }
            }

            if ( index == rules.size( ) )
            {
                callback( session );
            }
        }
    }
}

#endif  /* _RESTBED_DETAIL_RULE_ENGINE_H */
