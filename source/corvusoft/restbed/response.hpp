/*
 * Copyright 2013-2018, Corvusoft Ltd, All Rights Reserved.
 */

#pragma once

//System Includes
#include <map>
#include <string>
#include <limits>
#include <memory>
#include <cstdint>
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
    class Http;
    
    namespace detail
    {
        struct ResponseImpl;
    }
    
    class Response
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Response( void );
            
            virtual ~Response( void );
            
            //Functionality
            bool has_header( const std::string& name ) const;
            
            //Getters
            Bytes get_body( void ) const;
            
            double get_version( void ) const;
            
            int get_status_code( void ) const;
            
            std::string get_protocol( void ) const;
            
            std::string get_status_message( void ) const;
            
            void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            template< typename Type, typename std::enable_if< std::is_arithmetic< Type >::value, Type >::type = 0 >
            Type get_header( const std::string& name, const Type default_value ) const
            {
                return Common::parse_parameter( get_header( name ), default_value );
            }
            
            std::string get_header( const std::string& name, const std::string& default_value ) const;
            
            std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            //Setters
            void set_body( const Bytes& value );
            
            void set_body( const std::string& value );
            
            void set_version( const double value );
            
            void set_status_code( const int value );
            
            void set_protocol( const std::string& protocol );
            
            void set_status_message( const std::string& value );

            void add_header( const std::string& name, const std::string& value );

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
            friend Http;
            
            //Definitions
            
            //Constructors
            Response( const Response& original ) = delete;
            
            //Functionality
            
            //Getters
            
            //Setters
            
            //Operators
            Response& operator =( const Response& value ) = delete;
            
            //Properties
            std::unique_ptr< detail::ResponseImpl > m_pimpl;
    };
}
