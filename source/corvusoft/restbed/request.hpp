/*
 * Copyright (c) 2013, 2014, 2015 Corvusoft
 */

#ifndef _RESTBED_REQUEST_H
#define _RESTBED_REQUEST_H 1

//System Includes
#include <map>
#include <string>
#include <functional>

//Project Includes
#include <corvusoft/restbed/byte.hpp>

//External Includes

//System Namespaces

//Project Namespaces

//External Namespaces

namespace restbed
{
    //Forward Declarations
    
    namespace detail
    {
        class SessionImpl;
        class ServiceImpl;
        struct RequestImpl;
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
            
            const Bytes& get_body( void ) const;
            
            std::string get_path( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::string get_method( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            std::string get_protocol( const std::function< std::string ( const std::string& ) >& transform = nullptr ) const;
            
            void get_body( std::string& body, const std::function< std::string ( const Bytes& ) >& transform = nullptr ) const;
            
            void get_header( const std::string& name, int& value, const int default_value = 0 ) const;
            
            void get_header( const std::string& name, long& value, const long default_value = 0 ) const;
            
            void get_header( const std::string& name, float& value, const float default_value = 0 ) const;
            
            void get_header( const std::string& name, double& value, const double default_value = 0 ) const;

            void get_header( const std::string& name, long long& value, const long long default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;
            
            void get_header( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;

            std::multimap< std::string, std::string > get_headers( const std::string& name = "" ) const;
            
            std::string get_header( const std::string& name, const std::string& default_value = "" ) const;
            
            std::string get_header( const std::string& name, const std::function< std::string ( const std::string& ) >& transform ) const;
            
            void get_query_parameter( const std::string& name, int& value, const int default_value = 0 ) const;
            
            void get_query_parameter( const std::string& name, long& value, const long default_value = 0 ) const;
            
            void get_query_parameter( const std::string& name, float& value, const float default_value = 0 ) const;
            
            void get_query_parameter( const std::string& name, double& value, const double default_value = 0 ) const;

            void get_query_parameter( const std::string& name, long long& value, const long long default_value = 0 ) const;
            
            void get_query_parameter( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;
            
            void get_query_parameter( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;

            void get_query_parameter( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;
            
            std::string get_query_parameter( const std::string& name, const bool ignore_case = true ) const;
            
            std::string get_query_parameter( const std::string& name, const std::string& default_value, bool ignore_case = true ) const;
            
            std::string get_query_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform, bool ignore_case = true ) const;
            
            std::multimap< std::string, std::string > get_query_parameters( const std::string& name = "", const bool ignore_case = true ) const;
            
            void get_path_parameter( const std::string& name, int& value, const int default_value = 0 ) const;
            
            void get_path_parameter( const std::string& name, long& value, const long default_value = 0 ) const;
            
            void get_path_parameter( const std::string& name, float& value, const float default_value = 0 ) const;
            
            void get_path_parameter( const std::string& name, double& value, const double default_value = 0 ) const;

            void get_path_parameter( const std::string& name, long long& value, const long long default_value = 0 ) const;
            
            void get_path_parameter( const std::string& name, unsigned int& value, const unsigned int default_value = 0 ) const;
            
            void get_path_parameter( const std::string& name, unsigned long& value, const unsigned long default_value = 0 ) const;

            void get_path_parameter( const std::string& name, unsigned long long& value, const unsigned long long default_value = 0 ) const;
            
            std::string get_path_parameter( const std::string& name, const bool ignore_case = true ) const;
            
            std::string get_path_parameter( const std::string& name, const std::string& default_value, bool ignore_case = true ) const;
            
            std::string get_path_parameter( const std::string& name, const std::function< std::string ( const std::string& ) >& transform, bool ignore_case = true ) const;
            
            std::map< std::string, std::string > get_path_parameters( const std::string& name = "", const bool ignore_case = true ) const;
            
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
            detail::RequestImpl* m_pimpl;
    };
}

#endif  /* _RESTBED_REQUEST_H */
