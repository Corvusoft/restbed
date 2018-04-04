/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <limits>
#include <string>
#include <memory>
#include <cstdint>
#include <stdexcept>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>
#include <corvusoft/restbed/common.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    class Uri;
    class Http;
    class Session;
    class Response;
    
    namespace detail
    {
        class HttpImpl;
        class SessionImpl;
        class ServiceImpl;
        struct RequestImpl;
        class WebSocketManagerImpl;
    }
    
    class Request
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Request( void );
            
            Request( const Uri& value );
            
            virtual ~Request( void );
            
            //Functionality
            bool has_header( const std::string& name ) const;
            
            bool has_path_parameter( const std::string& name ) const;
            
            bool has_query_parameter( const std::string& name ) const;
            
            //Getters
            uint16_t get_port( void ) const;
            
            double get_version( void ) const;
            
            const Bytes& get_body( void ) const;
            
            const std::shared_ptr< const Response > get_response( void ) const;
            
            std::string get_host( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            float get_header( const std::string& name, const float default_value ) const;
            
            double get_header( const std::string& name, const double default_value ) const;
            
            std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
            
            std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
            Type get_header( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_header( name ), default_value );
            }
            
            std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            float get_query_parameter( const std::string& name, const float default_value ) const;
            
            double get_query_parameter( const std::string& name, const double default_value ) const;
            
            std::string get_query_parameter( const std::string& name, const std::string& default_value = "" ) const;
            
            std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
            Type get_query_parameter( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_query_parameter( name ), default_value );
            }
            
            std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "" ) const;
            
            float get_path_parameter( const std::string& name, const float default_value ) const;
            
            double get_path_parameter( const std::string& name, const double default_value ) const;
            
            std::string get_path_parameter( const std::string& name, const std::string& default_value = "" ) const;
            
            std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
            Type get_path_parameter( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_path_parameter( name ), default_value );
            }
            
            std::map< std::string, std::string > get_path_parameters( const std::string& name = "" ) const;
            
            //Setters
            void set_body( const Bytes& value );
            
            void set_body( const std::string& value );
            
            void set_port( const uint16_t value );
            
            void set_version( const double value );
            
            void set_path( const std::string& value );
            
            void set_host( const std::string& value );
            
            void set_method( const std::string& value );
            
            void set_protocol( const std::string& value );
            
            void add_header( const std::string& name, const std::string& value );
            
            void set_header( const std::string& name, const std::string& value );
            
            void set_headers( const std::multimap< std::string, std::string >& values );
            
            void set_query_parameter( const std::string& name, const std::string& value );
            
            void set_query_parameters( const std::multimap< std::string, std::string >& values );
            
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
            friend Http;
            friend Session;
            friend detail::HttpImpl;
            friend detail::SessionImpl;
            friend detail::ServiceImpl;
            friend detail::WebSocketManagerImpl;
            
            //Definitions
            
            //Constructors
            Request( const Request& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Request& operator =( const Request& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::RequestImpl > m_pimpl;
    };
}
