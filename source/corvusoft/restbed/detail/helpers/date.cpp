/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/helpers/date.h"

//External Includes

//System Namespaces
using std::ctime;
using std::string;
using std::chrono::time_point;
using std::chrono::system_clock;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        namespace helpers
        {
            string Date::format( const time_point< system_clock >& value )
            {
                time_t time = system_clock::to_time_t( value );
                
                string date = ctime( &time );
                date.erase( date.length( ) - 1 );
                
                return date;
            }
        }
    }
}
