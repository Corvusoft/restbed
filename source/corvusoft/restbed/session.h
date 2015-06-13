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

#ifndef _RESTBED_SESSION_H
#define _RESTBED_SESSION_H 1

//System Includes
#include <map>
#include <chrono>
#include <string>
#include <memory>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/byte>
#include <corvusoft/framework/string>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Request;
    class Session;
    class Resource;
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
    }
    
    class Session
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Session( const std::string& id );

            virtual ~Session( void );
            
            //Functionality
            bool is_open( void ) const;

            bool is_closed( void ) const;

            void purge( const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void close( const framework::Bytes& body );

            void close( const std::string& body = framework::String::empty );

            void close( const int status, const framework::Bytes& body );

            void close( const int status, const std::string& body = framework::String::empty );

            void close( const int status, const std::multimap< std::string, std::string >& headers );

            void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

            void close( const int status, const framework::Bytes& body, const std::multimap< std::string, std::string >& headers );

            void yield( const std::string& data, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const framework::Bytes& data, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const int status, const std::string& body, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const int status, const framework::Bytes& body = { }, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const int status, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void yield( const int status, const framework::Bytes& body, const std::multimap< std::string, std::string >& headers, const std::function< void ( const std::shared_ptr< Session >& ) >& callback = nullptr );

            void fetch( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session >&, const framework::Bytes& ) >& callback );

            void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session >&, const framework::Bytes& ) >& callback );

            void wait_for( const std::chrono::hours& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void wait_for( const std::chrono::minutes& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void wait_for( const std::chrono::seconds& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void wait_for( const std::chrono::milliseconds& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            void wait_for( const std::chrono::microseconds& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

            //Getters
            const std::string& get_id( void ) const;

            const std::string& get_origin( void ) const;

            const std::string& get_destination( void ) const;

            const std::shared_ptr< const Request > get_request(  void ) const;

            const std::shared_ptr< const Resource > get_resource( void ) const;

            const std::multimap< std::string, std::string >& get_headers( void ) const;

            //Setters
            void set_header( const std::string& name, const std::string& value );

            void set_headers( const std::multimap< std::string, std::string >& values );
            
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
            friend detail::ServiceImpl;
            friend detail::SessionImpl;

            //Definitions
            
            //Constructors
            Session( void ) = delete;

            Session( const Session& original ) = delete;
            
            //Functionality

            //Getters
            
            //Setters
            
            //Operators
            Session& operator =( const Session& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::SessionImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_SESSION_H */
