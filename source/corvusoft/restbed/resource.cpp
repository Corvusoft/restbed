/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 *
 * http://corvusoft.co.uk/license
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//System Includes

//Project Includes
#include "corvusoft/restbed/session.h"
#include "corvusoft/restbed/resource.h"
#include "corvusoft/restbed/detail/resource_impl.h"

//External Includes

//System Namespaces
using std::set;
using std::string;
using std::multimap;
using std::function;
using std::exception;
using std::shared_ptr;

//Project Namespaces
using restbed::detail::ResourceImpl;

//External Namespaces

namespace restbed
{
    Resource::Resource( void ) : m_pimpl( new ResourceImpl )
    {
        return;
    }
    
    Resource::~Resource( void )
    {
        return;
    }

    void Resource::set_path( const string& value )
    {
        m_pimpl->set_paths( { value } );
    }

    void Resource::set_paths( const set< string >& values )
    {
        m_pimpl->set_paths( values );
    }

    void Resource::set_default_header( const string& name, const string& value )
    {
        m_pimpl->set_default_header( name, value );
    }

    void Resource::set_default_headers( const multimap< string, string >& values )
    {
        m_pimpl->set_default_headers( values );
    }

    void Resource::set_authentication_handler( const function< void ( const shared_ptr< Session >&, const function< void ( const shared_ptr< Session >& ) >& ) >& value )
    {
        m_pimpl->set_authentication_handler( value );
    }

    void Resource::set_error_handler( const function< void ( const int, const std::exception&, const shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_error_handler( value );
    }

    void Resource::set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value )
    {
        m_pimpl->set_failed_filter_validation_handler( value );
    }

    void Resource::set_method_handler( const string& method,
                                       const std::function< void ( const std::shared_ptr< Session >& ) >& callback )
    {
        static const multimap< string, string > empty;
        m_pimpl->set_method_handler( method, empty, callback );
    }
    
    void Resource::set_method_handler( const string& method,
                                       const multimap< string, string >& filters,
                                       const std::function< void ( const std::shared_ptr< Session >& ) >& callback )
    {
        m_pimpl->set_method_handler( method, filters, callback );
    }
}
