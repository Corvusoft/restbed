/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESPONSE_IMPL_H
#define _RESTBED_DETAIL_RESPONSE_IMPL_H 1

//System Includes
#include <map>
#include <memory>
#include <string>

//Project Includes

//External Includes
#include <corvusoft/framework/byte>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations

    namespace detail
    {
        //Forward Declarations
        
        class ResponseImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                ResponseImpl( void );

                virtual ~ResponseImpl( void );
                
                //Functionality
                framework::Bytes to_bytes( void ) const;

                //Getters
                double get_version( void ) const;
            
                int get_status_code( void ) const;

                const std::string& get_protocol( void ) const;
            
                const std::string& get_status_message( void ) const;

                const framework::Bytes& get_body( void ) const;

                const std::multimap< std::string, std::string >& get_headers( void ) const;
                
                //Setters
                void set_version( const double value );

                void set_status_code( const int value );

                void set_protocol( const std::string& value );
            
                void set_status_message( const std::string& value );

                void set_body( const framework::Bytes& value );
                
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
                ResponseImpl( const ResponseImpl& original ) = delete;

                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                ResponseImpl& operator =( const ResponseImpl& value ) = delete;
                
                //Properties
                double m_version;
            
                int m_status_code;

                std::string m_protocol;

                std::string m_status_message;

                framework::Bytes m_body;
            
                std::multimap< std::string, std::string > m_headers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESPONSE_IMPL_H */
