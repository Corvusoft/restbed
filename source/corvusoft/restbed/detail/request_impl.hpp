/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <cstdint>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes
#include <asio/streambuf.hpp>
#include <asio/io_service.hpp>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Response;
    
    namespace detail
    {
        //Forward Declarations
        class SocketImpl;
        
        struct RequestImpl
        {
            Bytes m_body { };
            
            uint16_t m_port = 80;
            
            double m_version = 1.1;
            
            std::string m_host = "";
            
            std::string m_path = "/";
            
            std::string m_method = "GET";
            
            std::string m_protocol = "HTTP";
            
            std::shared_ptr< Uri > m_uri = nullptr;
            
            std::shared_ptr< Response > m_response = nullptr;
            
            std::multimap< std::string, std::string > m_headers { };
            
            std::map< std::string, std::string > m_path_parameters { };
            
            std::multimap< std::string, std::string > m_query_parameters { };
            
            std::shared_ptr< asio::io_service > m_io_service = nullptr;
            
            std::shared_ptr< SocketImpl > m_socket = nullptr;
            
            std::shared_ptr< asio::streambuf > m_buffer = nullptr;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
