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

#ifndef _RESTBED_SESSION_MANAGER_H
#define _RESTBED_SESSION_MANAGER_H 1

//System Includes
#include <memory>
#include <functional>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Settings;
    
    class SessionManager
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors

            //Functionality
            virtual void stop( void ) = 0;

            virtual void start( const std::shared_ptr< const Settings >& settings ) = 0;

            virtual void create( const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            virtual void load( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            virtual void purge( std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback ) = 0;

            //Getters

            //Setters
            
            //Operators
            
            //Properties
            
        protected:
            SessionManager( void ) = default;

            SessionManager( const SessionManager& original ) = default;

            virtual ~SessionManager( void ) = default;

            //Functionality

            //Getters

            //Setters

            //Operators
            SessionManager& operator =( const SessionManager& value ) = default;

            //Properties

        private:
            //Friends
            
            //Definitions
            
            //Constructors

            //Functionality

            //Getters
            
            //Setters
            
            //Operators
            
            //Properties
    };
}

#endif  /* _RESTBED_SESSION_MANAGER_H */
