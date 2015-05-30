/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

//System Includes
#include <map>
#include <string>
#include <memory>
#include <string>
#include <functional>

//Project Includes

//External Includes
#include <corvusoft/framework/bytes>
#include <corvusoft/framework/string>

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        class RequestImpl;
        class SessionImpl;
        class ServiceImpl;
    }
    
    class Request
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors  
            Request( void );

            virtual ~Request( void );
            
            //Functionality            
            bool has_header( const std::string& name ) const;
            
            bool has_path_parameter( const std::string& name, const bool ignore_case = true ) const;
            
            bool has_query_parameter( const std::string& name, const bool ignore_case = true ) const;

            //Getters
            double get_version( void ) const;

            const std::string& get_path( void ) const;

            const std::string& get_method( void ) const;

            const std::string& get_protocol( void ) const;

            const std::shared_ptr< framework::Bytes >& get_body( void ) const;

//            std::string get_path( std::function< string ( string ) > transform = nullptr ) const;
//
//            std::string get_method( std::function< string ( string ) > transform = nullptr ) const;

            //framework::Bytes get_body( std::function< framework::Bytes ( const framework::Bytes& ) > transform = nullptr ) const;

            //framework::Bytes get_body( std::function< framework::Bytes ( const framework::Bytes& ) > transform = nullptr ) const;
//            
//            std::string get_origin( std::function< string ( string ) > transform = nullptr ) const;
//
//            std::string get_destination( std::function< string ( string ) > transform = nullptr ) const;
//        
//            std::string get_protocol( std::function< string ( string ) > transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ int& value,
                             const int default_value = 0,
                             const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ long& value,
                             const long default_value = 0,
                             const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ unsigned long& value,
                             const unsigned long default_value = 0,
                             const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ unsigned int& value,
                             const unsigned int default_value = 0,
                             const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ float& value,
                             const float default_value = 0,
                             const std::function< std::string ( const std::string& ) > transform = nullptr ) const;

            void get_header( const std::string& name,
                     /*out*/ double& value,
                             const double default_value = 0,
                             const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            std::string get_header( const std::string& name,
                                    const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            std::string get_header( const std::string& name,
                                    const std::string& default_value,
                                    const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

            std::multimap< std::string, std::string > get_headers( const std::string& name = framework::String::empty,
                                                                   const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

//            void get_query_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_query_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_query_parameter( const std::string& name, /*out*/ uint& value, std::function< string ( string ) > transform = nullptr);
//
//            void get_query_parameter( const std::string& name, /*out*/ float& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_query_parameter( const std::string& name, /*out*/ double& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_query_parameter( const std::string& name, /*out*/ string& value, std::function< string ( string ) > transform = nullptr );
//
//            std::string get_query_parameter( const std::string& name, const std::string& default_value = "", std::function< string ( string ) > transform = nullptr ) const;
//        
//            std::multimap< std::string, std::string > get_query_parameters( void ) const;
//        
//            std::multimap< std::string, std::string > get_query_parameters( const std::string& name ) const;

//            void get_path_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_path_parameter( const std::string& name, /*out*/ uint& value, std::function< string ( string ) > transform = nullptr);
//
//            void get_path_parameter( const std::string& name, /*out*/ float& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_path_parameter( const std::string& name, /*out*/ double& value, std::function< string ( string ) > transform = nullptr );
//
//            void get_path_parameter( const std::string& name, /*out*/ string& value, std::function< string ( string ) > transform = nullptr );
//
            std::string get_path_parameter( const std::string& name,
                                            const std::string& default_value = framework::String::empty,
                                            const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;

//            std::map< std::string, std::string > get_path_parameters( void ) const;

            //Setters
            
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
            friend detail::ServiceImpl;
            friend detail::SessionImpl;

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

#endif  /* _RESTBED_REQUEST_H */
