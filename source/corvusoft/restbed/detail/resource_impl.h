/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESOURCE_IMPL_H
#define _RESTBED_DETAIL_RESOURCE_IMPL_H 1

//System Includes
#include <map>
#include <set>
#include <memory>
#include <string>
#include <utility>
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
                
                ResourceImpl( const ResourceImpl& original );
                
                virtual ~ResourceImpl( void );
                
                //Functionality
                
                //Getters
                const std::string& get_id( void ) const;

                const std::set< std::string >& get_paths( void ) const;
                
                std::multimap< std::string, std::pair< std::multimap< std::string, std::string >, std::function< void ( const std::shared_ptr< Session >& ) > > >
                get_method_handlers( const std::string& method ) const;

                //Setters
                void set_paths( const std::set< std::string >& values );

                void set_method_handler( const std::string& method,
                                         const std::multimap< std::string, std::string >& filters,
                                         const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void set_authentication_handler( const std::function< bool ( const std::shared_ptr< Session >& ) >& value );
                
                void set_error_handler( const std::function< void ( const int, const std::shared_ptr< Session >& ) >& value );

                //Operators
                bool operator >( const ResourceImpl& value ) const;

                bool operator <( const ResourceImpl& value ) const;

                bool operator ==( const ResourceImpl& value ) const;
                
                bool operator !=( const ResourceImpl& value ) const;
                
                ResourceImpl& operator =( const ResourceImpl& value );
                
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
                
                //Functionality

                //Getters
                
                //Setters
                
                //Operators
                
                //Properties
                std::string m_id;

                std::set< std::string > m_paths;
                
                std::multimap< std::string,
                               std::pair< std::multimap< std::string, std::string >,
                               std::function< void ( const std::shared_ptr< Session >& ) > > > m_method_handlers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESOURCE_IMPL_H */
