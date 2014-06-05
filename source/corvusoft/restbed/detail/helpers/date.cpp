/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes
#include <iomanip>
#include <sstream>

//Project Includes
#include "corvusoft/restbed/detail/helpers/date.h"

//External Includes

//System Namespaces
using std::string;
using std::put_time;
using std::stringstream;
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
                time_t timestamp = system_clock::to_time_t( value );
                
                tm time = { };
                localtime_r( &timestamp, &time );
                
                stringstream date;
                date << put_time( &time, "%c" );
                
                return date.str( );
            }
        }
    }
}
