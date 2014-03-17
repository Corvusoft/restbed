/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/detail/helpers/istream.h"

//External Includes

//System Namespaces
using std::istream;

//Project Namespaces

//External Namespaces

namespace restbed
{
    namespace detail
    {
        namespace helpers
        {
            char IStream::reverse_peek( istream& socket )
            {
                socket.unget( );
                
                char previous_byte = socket.get( );
                
                return previous_byte;
            }
        }
    }
}
