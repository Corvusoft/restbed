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
#include "corvusoft/restbed/settings.h"
#include "corvusoft/restbed/detail/session_manager_impl.h"

//External Includes
#include <corvusoft/framework/unique_id>

//System Namespaces
using std::function;
using std::shared_ptr;
using std::make_shared;

//Project Namespaces

//External Namespaces
using framework::UniqueId;

namespace restbed
{
    namespace detail
    {
        SessionManagerImpl::SessionManagerImpl( void )
        {
            return;
        }

        SessionManagerImpl::~SessionManagerImpl( void )
        {
            return;
        }

        void SessionManagerImpl::stop( void )
        {
            return;
        }

        void SessionManagerImpl::start( const shared_ptr< const Settings >& )
        {
            return;
        }

        void SessionManagerImpl::create( const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            auto session = make_shared< Session >( UniqueId::generate( ).to_string( ) );
            callback( session );
        }

        void SessionManagerImpl::purge( shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            session.reset( );
            callback( nullptr );
        }

        void SessionManagerImpl::load( const shared_ptr< Session >& session, const function< void ( const shared_ptr< Session >& ) >& callback )
        {
            if ( session->is_closed( ) )
            {
                return;
            }

            callback( session );
        }
    }
}
