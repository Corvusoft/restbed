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

#ifndef _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H
#define _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H 1

//System Includes
#include <memory>

//Project Includes
#include "corvusoft/restbed/session_manager.h"

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Settings;
    
    namespace detail
    {
        //Forward Declarations
        
        class SessionManagerImpl : public SessionManager
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionManagerImpl( void );
            
                virtual ~SessionManagerImpl( void );
                
                //Functionality
                void stop( void );

                void start( const std::shared_ptr< const Settings >& settings );

                void create( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void purge( std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void load( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                //Getters

                //Setters
                
                //Operators
                
                //Properties
                
            protected:
                //Friends
                
                //Definitions
                
                //Constructors
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                
            private:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionManagerImpl( const SessionManagerImpl& original ) = delete;

                //Functionality

                //Getters
                
                //Setters
                
                //Operators
                SessionManagerImpl& operator =( const SessionManagerImpl& value ) = delete;
                
                //Properties
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_MANAGER_IMPL_H */
