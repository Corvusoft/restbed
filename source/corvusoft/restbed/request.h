/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

//System Includes
#include <map>
#include <memory>
#include <string>

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
        class RequestImpl;
    }
    
    class Request
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructors
            Request( void );
            
            Request( const Request& original );
        
            virtual ~Request( void );
            
            //Functionality            
            bool has_header( const std::string& name, const bool case_insensitive_search = true ) const;
            
            bool has_path_parameter( const std::string& name, const bool case_insensitive_search = true ) const;
            
            bool has_query_parameter( const std::string& name, const bool case_insensitive_search = true ) const;
            
            //Getters
            double get_version( void ) const;

            std::string get_path( std::function< string ( string ) > transfomer = nullptr ) const;

            std::string get_method( std::function< string ( string ) > transfomer = nullptr ) const;

            framework::Bytes get_body( std::function< framework::Bytes ( framework::Bytes ) > transfomer = nullptr ) const;
            
            std::string get_origin( std::function< string ( string ) > transfomer = nullptr ) const;

            std::string get_destination( std::function< string ( string ) > transfomer = nullptr ) const;
        
            std::string get_protocol( std::function< string ( string ) > transfomer = nullptr ) const;

//, const bool case_insensitive_search = true 
            void get_header( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ int& value, int default_value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ uint& value, std::function< string ( string ) > transfomer = nullptr);

            void get_header( const std::string& name, /*out*/ uint& value, uint default_value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ float& value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ float& value, float default_value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ double& value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ double& value, double default_value, std::function< string ( string ) > transfomer = nullptr );

            void get_header( const std::string& name, /*out*/ string& value, std::function< string ( string ) > transfomer = nullptr );

            std::string get_header( const std::string& name, const std::string& default_value = "", std::function< string ( string ) > transfomer = nullptr ) const;
            
            std::multimap< std::string, std::string > get_headers( void ) const;
        
            std::multimap< std::string, std::string > get_headers( const std::string& name ) const;
            
            void get_query_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transfomer = nullptr );

            void get_query_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transfomer = nullptr );

            void get_query_parameter( const std::string& name, /*out*/ uint& value, std::function< string ( string ) > transfomer = nullptr);

            void get_query_parameter( const std::string& name, /*out*/ float& value, std::function< string ( string ) > transfomer = nullptr );

            void get_query_parameter( const std::string& name, /*out*/ double& value, std::function< string ( string ) > transfomer = nullptr );

            void get_query_parameter( const std::string& name, /*out*/ string& value, std::function< string ( string ) > transfomer = nullptr );

            std::string get_query_parameter( const std::string& name, const std::string& default_value = "", std::function< string ( string ) > transfomer = nullptr ) const;
        
            std::multimap< std::string, std::string > get_query_parameters( void ) const;
        
            std::multimap< std::string, std::string > get_query_parameters( const std::string& name ) const;
            
            void get_path_parameter( const std::string& name, /*out*/ int& value, std::function< string ( string ) > transfomer = nullptr );

            void get_path_parameter( const std::string& name, /*out*/ uint& value, std::function< string ( string ) > transfomer = nullptr);

            void get_path_parameter( const std::string& name, /*out*/ float& value, std::function< string ( string ) > transfomer = nullptr );

            void get_path_parameter( const std::string& name, /*out*/ double& value, std::function< string ( string ) > transfomer = nullptr );

            void get_path_parameter( const std::string& name, /*out*/ string& value, std::function< string ( string ) > transfomer = nullptr );

            std::string get_path_parameter( const std::string& name, const std::string& default_value = "", std::function< string ( string ) > transfomer = nullptr ) const;
            
            std::map< std::string, std::string > get_path_parameters( void ) const;
            
            //Setters
            
            //Operators
            Request& operator =( const Request& value );
            
            bool operator <( const Request& value ) const;
            
            bool operator >( const Request& value ) const;
            
            bool operator ==( const Request& value ) const;
            
            bool operator !=( const Request& value ) const;
            
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
            std::unique_ptr< detail::RequestImpl > m_pimpl;
    };
}

#endif  /* _RESTBED_REQUEST_H */
