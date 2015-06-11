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

#ifndef _RESTBED_DETAIL_RESOURCE_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_IMPL_H 1

//System Includes
#include <map>
#include <set>
#include <memory>
#include <string>
#include <utility>
#include <stdexcept>
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
    
    namespace detail
    {
        //Forward Declarations
        
        class ResourceImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ResourceImpl( void );
                
                virtual ~ResourceImpl( void );
                
                //Functionality
                void authenticate( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                //Getters
                const std::set< std::string >& get_paths( void ) const;

                const std::set< std::string >& get_methods( void ) const;

                const std::multimap< std::string, std::string >& get_default_headers( void ) const;

                const std::function< void ( const std::shared_ptr< Session >& ) >& get_failed_filter_validation_handler( void ) const;

                const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session >& ) > get_error_handler( void ) const;

                std::multimap< std::string, std::pair< std::multimap< std::string, std::string >, std::function< void ( const std::shared_ptr< Session >& ) > > > get_method_handlers( const std::string& method ) const;

                //Setters
                void set_paths( const std::set< std::string >& values );

                void set_default_header( const std::string& name, const std::string& value );

                void set_default_headers( const std::multimap< std::string, std::string >& values );

                void set_authentication_handler( const std::function< void ( const std::shared_ptr< Session >&,
                                                                        const std::function< void ( const std::shared_ptr< Session >& ) >& ) >& value );

                void set_error_handler( const std::function< void ( const int, const std::exception&, const std::shared_ptr< Session >& ) >& value );

                void set_failed_filter_validation_handler( const std::function< void ( const std::shared_ptr< Session >& ) >& value );

                void set_method_handler( const std::string& method, const std::multimap< std::string, std::string >& filters, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

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
                ResourceImpl( const ResourceImpl& original ) = delete;
                
                //Functionality

                //Getters
                
                //Setters
                
                //Operators
                ResourceImpl& operator =( const ResourceImpl& value ) = delete;

                //Properties
                std::set< std::string > m_paths;

                std::set< std::string > m_methods;

                std::multimap< std::string, std::string > m_default_headers;

                std::function< void ( const int, const std::exception&, const std::shared_ptr< Session >& ) > m_error_handler;

                std::function< void ( const std::shared_ptr< Session >&, const std::function< void ( const std::shared_ptr< Session >& ) >& ) > m_authentication_handler;

                std::function< void ( const std::shared_ptr< Session >& ) > m_failed_filter_validation_handler;

                std::multimap< std::string, std::pair< std::multimap< std::string, std::string >, std::function< void ( const std::shared_ptr< Session >& ) > > > m_method_handlers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_IMPL_H */
