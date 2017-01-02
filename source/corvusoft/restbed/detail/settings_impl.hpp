/*
 * Copyright 2013-2017, Corvusoft Ltd, All Rights Reserved.
 */

#ifndef _RESTBED_DETAIL_SETTINGS_IMPL_H
#define _RESTBED_DETAIL_SETTINGS_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <cstdint>

//Project Includes

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class SSLSettings;
    
    namespace detail
    {
        //Forward Declarations
        
        struct SettingsImpl
        {
            uint16_t m_port = 80;
            
            std::string m_root = "/";
            
            unsigned int m_worker_limit = 0;
            
            unsigned int m_connection_limit = 128;
            
            std::string m_bind_address = "";
            
            bool m_case_insensitive_uris = true;
            
            std::map< std::string, std::string > m_properties { };
            
            std::shared_ptr< const SSLSettings > m_ssl_settings = nullptr;
            
            std::multimap< std::string, std::string > m_default_headers { };
            
            std::chrono::milliseconds m_connection_timeout = std::chrono::milliseconds( 5000 );
            
            std::map< int, std::string > m_status_messages
            {
                { 100, "Continue" },
                { 101, "Switching Protocols" },
                { 102, "Processing" },
                { 200, "OK" },
                { 201, "Created" },
                { 202, "Accepted" },
                { 203, "Non-Authoritative Information" },
                { 204, "No Content" },
                { 205, "Reset Content" },
                { 206, "Partial Content" },
                { 207, "Multi-Status" },
                { 208, "Already Reported" },
                { 226, "IM Used" },
                { 300, "Multiple Choices" },
                { 301, "Moved Permanently" },
                { 302, "Found" },
                { 303, "See Other" },
                { 304, "Not Modified" },
                { 305, "Use Proxy" },
                { 306, "Reserved" },
                { 307, "Temporary Redirect" },
                { 308, "Permanent Redirect" },
                { 400, "Bad Request" },
                { 401, "Unauthorized" },
                { 402, "Payment Required" },
                { 403, "Forbidden" },
                { 404, "Not Found" },
                { 405, "Method Not Allowed" },
                { 406, "Not Acceptable" },
                { 407, "Proxy Authentication Required" },
                { 408, "Request Timeout" },
                { 409, "Conflict" },
                { 410, "Gone" },
                { 411, "Length Required" },
                { 412, "Precondition Failed" },
                { 413, "Request Entity Too Large" },
                { 414, "Request URI Too Long" },
                { 415, "Unsupported Media Type" },
                { 416, "Requested Range Not Satisfiable" },
                { 417, "Expectation Failed" },
                { 422, "Unprocessable Entity" },
                { 423, "Locked" },
                { 424, "Failed Dependency" },
                { 426, "Upgrade Required" },
                { 428, "Precondition Required" },
                { 429, "Too Many Requests" },
                { 431, "Request Header Fields Too Large" },
                { 500, "Internal Server Error" },
                { 501, "Not Implemented" },
                { 502, "Bad Gateway" },
                { 503, "Service Unavailable" },
                { 504, "Gateway Timeout" },
                { 505, "HTTP Version Not Supported" },
                { 506, "Variant Also Negotiates" },
                { 507, "Insufficient Storage" },
                { 508, "Loop Detected" },
                { 510, "Not Extended" },
                { 511, "Network Authentication Required" }
            };
        };
    }
}

#endif  /* _RESTBED_DETAIL_SETTINGS_IMPL_H */
