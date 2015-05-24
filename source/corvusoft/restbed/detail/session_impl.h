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

                void close( void );

                void close( const int status, const std::string& status_message );

                void fetch( const std::shared_ptr< Session >& session,
                            const std::function< void ( const std::shared_ptr< Session >& ) >& callback );

//                void close( void );
//
//                void close( const Response& value );
//
//                void close( uint16_t status_code );
//
//                void close( uint16_t status_code, Bytes& body );
//
//                void close( uint16_t status_code, multimap< string, string > headers, Bytes& body );
//
//                void yield( const Response& value ); //send response and call this function again with request.
//
//                void yield( const Response& value, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
//
//                void yield( uint16_t status_code, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
//
//                void yield( uint16_t status_code, Bytes& body, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
//
//                void yield( uint16_t status_code, multimap< string, string > headers, Bytes& body, const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
//
//                void fetch( const std::function< void ( const std::shared_ptr< Session >& ) >& callback );
//
//                void fetch( const Request& value, const std::size_t length, const std::function< void ( const std::shared_ptr< Session >& ) >& read_callback );
//
//                void wait_for( const std::chrono::seconds& delay, const std::function< void ( const std::shared_ptr< Session >& ) >& expired_callback );
//
//                void wait_for( const std::chrono::seconds& delay, const std::size_t iterations, const std::function< void ( const std::shared_ptr< Session >& ) >& expired_callback );
//
                  //void wait_until( func, cond var );
//                void wait_for( const std::chrono::seconds& delay, const std::size_t iterations, const std::function< bool ( const std::shared_ptr< Session >& ) >& trigger, const std::function< void ( const std::shared_ptr< Session >& ) >& triggered_callback );

                //Getters
//                const Request& get_request( void ) const;
                const std::string& get_id( void ) const;

                const std::shared_ptr< Request >& get_request( void ) const;

                const std::shared_ptr< Resource >& get_resource( void ) const;

                //Setters
                void set_id( const std::string& value );

                void set_request( const std::shared_ptr< Request >& value );

                void set_resource( const std::shared_ptr< Resource >& value );

                void set_socket( const std::shared_ptr< asio::ip::tcp::socket >& value );
                
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
                //Getters
                
                //Setters
                
                //Operators
                SessionImpl& operator =( const SessionImpl& value ) = delete;
                
                //Properties
                std::string m_id;

                std::shared_ptr< Request > m_request;

                std::shared_ptr< Resource > m_resource;

                std::shared_ptr< asio::streambuf > m_buffer; //just pass as argument?

                std::shared_ptr< asio::ip::tcp::socket > m_socket;
        };
    }
}

#endif  /* _RESTBED_DETAIL_SESSION_IMPL_H */
