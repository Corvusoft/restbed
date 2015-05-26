/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_DETAIL_REQUEST_IMPL_H
#define _RESTBED_DETAIL_REQUEST_IMPL_H 1

//System Includes
#include <map>
#include <memory>
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
        
        class RequestImpl
        {
            public:
                //Friends
                
                //Definitions
                
                //Constructors
                RequestImpl( void );
                
                virtual ~RequestImpl( void );
                
                //Functionality
                double get_version( void ) const;

                const std::string& get_path( void ) const;

                const std::string& get_method( void ) const;

                const std::string& get_protocol( void ) const;

                // bool has_header( const std::string& name ) const;
                
                // bool has_path_parameter( const std::string& name ) const;
                
                // bool has_query_parameter( const std::string& name ) const;
                
                //Getters
//                framework::Bytes get_body( void );

//                double get_version( void ) const;
//                
//                std::string get_path( void ) const;
//                
//                std::string get_method( void ) const;
//                
//                std::string get_origin( void ) const;
//
//                std::string get_destination( void ) const;
//            
//                std::string get_protocol( void ) const;
//                
//                std::string get_header( const std::string& name, const std::string& default_value ) const;
//                
//                std::multimap< std::string, std::string > get_headers( void ) const;
//
                  std::multimap< std::string, std::string > get_headers( const std::string& name,
                                                                         const std::function< std::string ( const std::string& ) >& transform ) const;

                  std::string get_path_parameter( const std::string& name,
                                                  const std::string& default_value,
                                                  std::function< std::string ( const std::string& ) > transform ) const;

//                std::string get_query_parameter( const std::string& name, const std::string& default_value ) const;
//                
//                std::multimap< std::string, std::string > get_query_parameters( void ) const;
//            
//                std::multimap< std::string, std::string > get_query_parameters( const std::string& name ) const;
//                
//                std::string get_path_parameter( const std::string& name, const std::string& default_value ) const;
//                
//                std::map< std::string, std::string > get_path_parameters( void ) const;

                //Setters
//                void set_body( const framework::Bytes& value );
//                
                void set_version( const double value );
//                
                void set_path( const std::string& value );
//                
                void set_method( const std::string& value );
//                
//                void set_origin( const std::string& value );
//
//                void set_destination( const std::string& value );
//            
                void set_protocol( const std::string& value );

                void set_headers( const std::multimap< std::string, std::string >& values );
//                
                void set_path_parameter( const std::string& name, const std::string& value );

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
                
                //Definitions
                
                //Constructors
                RequestImpl( const RequestImpl& original ) = delete;
                
                //Functionality
                
                //Getters
                
                //Setters
                
                //Operators
                RequestImpl& operator =( const RequestImpl& value ) = delete;
                
                //Properties
                framework::Bytes m_body;
                
                double m_version;
                
                std::string m_path;
                
                std::string m_method;
                
                std::string m_origin;

                std::string m_destination;
            
                std::string m_protocol;
            
                std::multimap< std::string, std::string > m_headers;
                
                std::map< std::string, std::string > m_path_parameters;
                
                std::multimap< std::string, std::string > m_query_parameters;
        };
    }
}

#endif  /* _RESTBED_DETAIL_REQUEST_IMPL_H */
