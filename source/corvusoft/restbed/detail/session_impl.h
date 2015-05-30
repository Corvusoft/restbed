/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_SESSION_IMPL_H
#define _RESTBED_DETAIL_SESSION_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <istream>
#include <functional>

//Project Includes

//External Includes
#include <asio.hpp>
#include <corvusoft/framework/bytes>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Session;
    class Request;
    class Response;
    class Resource;
    class Settings;
    
    namespace detail
    {
        //Forward Declarations
        
        class SessionImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                SessionImpl( void );
                
                virtual ~SessionImpl( void );
                
                //Functionality
                bool is_open( void ) const;

                bool is_closed( void ) const;

                void purge( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void close( void );

                void close( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

                void yield( const int status, const std::string& body, const std::multimap< std::string, std::string >& headers );

                void fetch( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void fetch( const std::size_t length, const std::function< void ( const std::shared_ptr< Session >&, const std::shared_ptr< framework::Bytes >& ) >& callback );

                void fetch( const std::string& delimiter, const std::function< void ( const std::shared_ptr< Session >&, const std::shared_ptr< framework::Bytes >& ) >& callback );

                void fetch( const std::shared_ptr< Session >& session, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                //Getters
                const std::string& get_id( void ) const;

                const std::string& get_origin( void ) const;

                const std::string& get_destination( void ) const;

                const std::shared_ptr< const Request >& get_request( void ) const;

                const std::shared_ptr< const Resource >& get_resource( void ) const;

                const std::multimap< std::string, std::string >& get_headers( void ) const;

                //Setters
                void set_id( const std::string& value );

                void set_origin( const std::string& value );

                void set_destination( const std::string& value );

                void set_request( const std::shared_ptr< Request >& value );

                void set_resource( const std::shared_ptr< Resource >& value );

                void set_settings( const std::shared_ptr< Settings >& value );

                void set_socket( const std::shared_ptr< asio::ip::tcp::socket >& value );

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
                
                //Definitions
                
                //Constructors
                
                //Functionality
                static const std::map< std::string, std::string > parse_request_line( std::istream& stream );

                static const std::multimap< std::string, std::string > parse_request_headers( std::istream& stream );

                void parse_request( const asio::error_code& error,
                                    const std::shared_ptr< Session >& session,
                                    const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

                void transmit( Response& response, const std::function< void ( const asio::error_code&, std::size_t ) >& callback ) const;

                //Getters
                
                //Setters
                
                //Operators
                SessionImpl& operator =( const SessionImpl& value ) = delete;
                
                //Properties
                bool m_is_closed;

                std::string m_id;

                std::string m_origin;

                std::string m_destination;

                std::shared_ptr< Session > m_session;

                std::shared_ptr< Request > m_request;

                std::shared_ptr< Resource > m_resource;

                std::shared_ptr< Settings > m_settings;

                std::shared_ptr< asio::streambuf > m_buffer;

                std::shared_ptr< asio::ip::tcp::socket > m_socket;

                std::multimap< std::string, std::string > m_headers;

                std::function< void ( const std::shared_ptr< Session >& ) > m_router;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_IMPL_H */
