/*
 * Site: restbed.corvusoft.co.uk
 * Author: Ben Crowhurst
 *
 * Copyright (c) 2013 Restbed Core Development Team and Community Contributors
 *
 * This file is part of Restbed.
 *
 * Restbed is free software: you can redistribute it and/or modify
 * it under the terms of the Lesser GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Restbed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the Lesser GNU General Public License
 * along with Restbed.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _RESTBED_DETAIL_SERVICE_IMPL_H
#define _RESTBED_DETAIL_SERVICE_IMPL_H 1

//System Includes
#include <list>
#include <memory>
#include <string>
#include <istream>

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
    class Resource;
    class Settings;

    enum LogLevel : int;
    
    namespace detail
    {
        //Forward Declarations
        
        class ServiceImpl
        {
            public:
                //Friends
                
                //Definitions

                //Constructors
                ServiceImpl( const Settings& settings );
                
                ServiceImpl( const ServiceImpl& original );

                virtual ~ServiceImpl( void );
                
                //Functionality
                void start( void );

                void stop( void );

                void publish( const Resource& value );

                void suppress( const Resource& value );

                virtual void error_handler( const Request& request, Response& response );

                virtual void authentication_handler( const Request& request, Response& response );

                virtual void log_handler( const LogLevel level, const std::string& format, ... );

                //Getters
                
                //Setters

                //Operators
                bool operator <( const ServiceImpl& rhs ) const;
                
                bool operator >( const ServiceImpl& rhs ) const;
                
                bool operator ==( const ServiceImpl& rhs ) const;
                
                bool operator !=( const ServiceImpl& rhs ) const;

                ServiceImpl& operator =( const ServiceImpl& rhs );

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
                void listen( void );

                //void build_request_path( std::istream& stream, Request& request, std::shared_ptr< asio::ip::tcp::socket >& socket );

                //void build_request_method( std::istream& stream, Request& request );

                //void build_request_version( std::istream& stream, Request& request );

                //void build_request_headers( std::istream& stream, Request& request );

                Request parse_incoming_request( std::shared_ptr< asio::ip::tcp::socket >& socket );

                void router( std::shared_ptr< asio::ip::tcp::socket > socket, const asio::error_code& error );

                //Getters
                
                //Setters
                
                //Operators

                //Properties
                uint16_t m_port;
            
                std::string m_root;

                std::list< Resource > m_resources; //thread-safe container

                std::shared_ptr< asio::io_service > m_io_service;

                std::shared_ptr< asio::ip::tcp::acceptor > m_acceptor;                
        };
    }
}

#endif  /* _RESTBED_DETAIL_SERVICE_IMPL_H */
