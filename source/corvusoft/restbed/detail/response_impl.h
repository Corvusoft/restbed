/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_RESPONSE_IMPL_H
#define _RESTBED_DETAIL_RESPONSE_IMPL_H 1

//System Includes
#include <map>
#include <string>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/bytes>

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
                
                ResponseImpl( const ResponseImpl& original );
                
                virtual ~ResponseImpl( void );
                
                //Functionality
                bool has_header( const std::string& name ) const;

                //Getters
                framework::Bytes get_body( void ) const;

                std::function< framework::Bytes ( void ) > get_body_callback( void ) const;
            
                double get_version( void ) const;
            
                int get_status_code( void ) const;
            
                std::string get_status_message( void ) const;
            
                std::string get_header( const std::string& name ) const;
                
                std::multimap< std::string, std::string > get_headers( void ) const;

                std::multimap< std::string, std::string > get_headers( const std::string& name ) const;
                
                //Setters
                void set_body( const std::string& value );

                void set_body( const framework::Bytes& value );

                void set_body_callback( const std::function< framework::Bytes ( void ) >& value );
            
                void set_version( const double value );
            
                void set_status_code( const int value );
            
                void set_status_message( const std::string& value );
                
                void set_header( const std::string& name, const std::string& value );
                
                void set_headers( const std::multimap< std::string, std::string >& values );
                
                //Operators
                bool operator <( const ResponseImpl& value ) const;
                
                bool operator >( const ResponseImpl& value ) const;
                
                bool operator ==( const ResponseImpl& value ) const;
                
                bool operator !=( const ResponseImpl& value ) const;
                
                ResponseImpl& operator =( const ResponseImpl& value );
                
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
                framework::Bytes m_body;

                std::function< framework::Bytes ( void ) > m_body_callback;
            
                double m_version;
            
                int m_status_code;
            
                std::string m_status_message;
            
                std::multimap< std::string, std::string > m_headers;
        };
    }
}

#endif  /* _RESTBED_DETAIL_RESPONSE_IMPL_H */
