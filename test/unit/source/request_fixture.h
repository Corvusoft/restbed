/*
 * Copyright (c) 2013, 2014 Corvusoft
 */

#ifndef _REQUEST_FIXTURE_H
#define _REQUEST_FIXTURE_H 1

//System Includes
#include <map>
#include <string>

//Project Includes
#include <corvusoft/restbed/request>
#include <corvusoft/restbed/detail/request_impl.h>

//External Includes
#include <corvusoft/framework/bytes>

//System Namespaces
using std::map;
using std::string;

//Project Namespaces
using restbed::Request;

//External Namespaces
using framework::Bytes;

class RequestFixture : public Request
{
    public:
        //Friends
        
        //Definitions
        
        //Constructors
        
        //Functionality
        
        //Getters
        
        //Setters
        void set_body( const Bytes& value )
        {
            m_pimpl->set_body( value );
        }
    
        void set_version( const double& value )
        {
            m_pimpl->set_version( value );
        }
    
        void set_path( const string& value )
        {
            m_pimpl->set_path( value );
        }
        
        void set_method( const string& value )
        {
            m_pimpl->set_method( value );
        }
    
        void set_origin( const string& value )
        {
            m_pimpl->set_origin( value );
        }

        void set_headers( const map< string, string>& value )
        {
            m_pimpl->set_headers( value );
        }
    
        void set_path_parameters( const map< string, string>& value )
        {
            m_pimpl->set_path_parameters( value );
        }
    
        void set_query_parameters( const map< string, string>& value )
        {
            m_pimpl->set_query_parameters( value );
        }
    
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
        
        //Functionality
        
        //Getters
        
        //Setters
        
        //Operators
        
        //Properties
};

#endif  /* _REQUEST_FIXTURE_H */
